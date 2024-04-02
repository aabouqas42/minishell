/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/02 07:27:34 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data *data;

	data = data_hook(NULL);
	if (!_strcmp(data->commands[0], "exit"))
		safe_exit(0);
	if (!_strcmp(data->commands[0], "c"))
		return (printf("\e[1;1H\e[2J"), 1);
	if (!_strcmp(data->commands[0], "clear"))
		return (printf("\e[1;1H\e[2J"), 1);
	if (!_strcmp(data->commands[0], "cd"))
		return (cd(data), 1);
	if (!_strcmp(data->commands[0], "echo"))
		return (echo(), 1);
	if (!_strcmp(data->commands[0], "pwd"))
		return (pwd(), 1);
	if (!_strcmp(data->commands[0], "env"))
		return (env_print(data->env), 1);
	if (!_strcmp(data->commands[0], "export"))
		return (export(), 1);
	return (0);
}

int	cmd_err()
{
	char	**commands;
	size_t	i;

	
	commands = data_hook(NULL)->commands;
	i = 0;
	while (commands[i])
	{
		if (arg_is_io_operator(commands[i]))
		{
			if ((i == 0 && arg_is_io_operator(commands[i]))
				|| (arg_is_io_operator(commands[i -1]) || arg_is_io_operator(commands[i +1])))
				// || commands[i +1] == NULL || arg_is_io_operator(commands[i +1]))
				return (printf("syntaxxx errrrr\n"), 1);
		}
		// if (commands[i][0] == '|' && (commands[i -1]|| commands[i +1] == NULL))
		// if ((commands[i][0] == '>' || commands[i][0] == '<' ) && (commands[i -1] == NULL || commands[i +1] == NULL))
		// 	return (printf("syntaxxx errrrr\n"), 1);
		i++;
	}
	return (0);
}

int	execute()
{
	t_data	*data;
	int		child_pid;

	data = data_hook(NULL);
	data->line = readline(data->prompt);
	if (data->line == NULL || *data->line == '\0')
		return (0);
	if (args_is_valid(data->line) == 0)
		return (perror("Invalid args\n"), data->exit_status = 127, 0);
	add_history(data->line);
	data->commands = _split(data->line);
	if (data->commands == NULL)
		return (1);
	if (builtins())
		return (0);
	if (is_valid_cmd(data, data->commands[0]) != 1)
	{
		printf("\e[31mminishell : %s command not found\e[0m\n", data->line);
		data->exit_status = 127 << 8;
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(data->program_path, data->commands, NULL);
	return (-1);
}

void	data_init(char **base_env)
{
	t_data	*data;
	char	*value;

	data = data_hook(NULL);
	data->commands = NULL;
	data->line = NULL;
	data->env = NULL;
	data->program_path = NULL;
	data->exit_status = 0;
	data->prompt = get_prompt();
	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=') + 1;
		*(value - 1) = '\0';
		env_export(*base_env, value);
		*(value - 1) = '=';
		base_env++;
	}
	if (env_grepvalue("PATH") == 0)
		env_export("PATH", get_paths_env());
}

void ex()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;
	// char	**commands;
	// int		i = 0;

	// atexit(ex);
	printf("\e[1;1H\e[2J");
	data_hook(&data);
	data_init(env);
	// goto h;
	while (1)
	{
		execute();
		waitpid(-1, &data.exit_status, 0);
		free (data.program_path);
		free (data.line);
		free_tab(data.commands);
		data.commands = NULL;
		data.program_path = NULL;
	}
	// h:
	// 	while (1)
	// 	{
	// 		i = 0;
	// 		commands = _split(readline("($)"));
	// 		while (commands[i])
	// 			printf("[%s]\n", commands[i++]);
	// 	}
	return (EXIT_SUCCESS);
}
