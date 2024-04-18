/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/18 18:28:47 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data *data;

	data = data_hook(NULL);
	if (!_strcmp(data->commands[0], "exit"))
		safe_exit(0);
	if (!_strcmp(data->commands[0], "cd"))
		return (cd(data), 1);
	if (!_strcmp(data->commands[0], "echo"))
		return (echo(), 1);
	if (!_strcmp(data->commands[0], "pwd"))
		return (pwd(), 1);
	if (!_strcmp(data->commands[0], "env"))
		return (env_print(data->env), 1);
	if (!_strcmp(data->commands[0], "export"))
		return (_export(), 1);
	return (0);
}

int	check_input()
{
	char	**cmds;
	int		i;

	cmds = data_hook(NULL)->commands;
	i = 0;
	while (cmds[i])
	{
		if ((i == 0 && is_io_op(cmds[i]))
			|| (is_io_op(cmds[i]) && cmds[i + 1] == NULL)
			|| (!_strcmp(cmds[i], "|") && !_strcmp(cmds[i + 1], "|")))
		{
			ft_putstr_fd("Syntax Error\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	request_input()
{
	t_data	*data;
	int		child_pid;

	data = data_hook(NULL);
	data->line = readline(data->prompt);
	if (data->line == NULL || *data->line == '\0')
		return (0);
	add_history(data->line);
	if (args_is_valid(data->line) == 0)
		return (do_error(SYNTAX_ERR), 0);
	data->commands = _split(data->line);
	if (check_input() == -1 || builtins())
		return (0);
	if (is_valid_cmd(data, data->commands[0]) != CMD_VALID)
	{
		printf("\e[31mminishell : %s command not found\e[0m\n", data->line);
		data->exit_status = 127 << 8;
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(data->program_path, data->commands, env_to_2darray());
	return (-1);
}

void	data_init(char **base_env)
{
	t_data		*data;
	char		*value;

	data = data_hook(NULL);
	ft_bzero(data, sizeof(t_data));
	data->prompt = get_prompt();
	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=');
		*(value) = '\0';
		if (_strcmp(*base_env, "SHLVL") == 0)
		{
			value = ft_itoa(ft_atoi(value +1) + 1);
			if (value == NULL)
				safe_exit(-1);
			env_export(*base_env, value);
		}else
			env_export(*base_env, value +1);
		*(value) = '=';
		base_env++;
	}
	if (env_grepvalue("PATH") == 0)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == 0)
		env_export("SHLVL", "1");
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	printf("\e[1;1H\e[2J");
	data_hook(&data);
	data_init(env);
	while (1)
	{
		request_input();
		waitpid(-1, &data.exit_status, 0);
		free (data.program_path);
		free (data.line);
		free_tab(data.commands);
		data.commands = NULL;
		data.program_path = NULL;
	}
	return (EXIT_SUCCESS);
}
