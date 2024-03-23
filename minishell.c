/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/23 15:39:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data *data;

	data = data_hook(NULL);
	if (!_strcmp(data->argv[0], "exit"))
		safe_exit(0);
	if (!_strcmp(data->argv[0], "c"))
		return (printf("\e[1;1H\e[2J"), 1);
	if (!_strcmp(data->argv[0], "clear"))
		return (printf("\e[1;1H\e[2J"), 1);
	if (!_strcmp(data->argv[0], "cd"))
		return (cd(data), 1);
	if (!_strcmp(data->argv[0], "echo"))
		return (echo(data), 1);
	if (!_strcmp(data->argv[0], "pwd"))
		return (pwd(), 1);
	if (!_strcmp(data->argv[0], "env"))
		return (env_print(data->env), 1);
	if (!_strcmp(data->argv[0], "export"))
		return (_export(data), 1);
	return (0);
}

int	execute()
{
	t_data *data;
	int	child_pid;

	data = data_hook(NULL);
	data->line = readline(data->prompt);
	if (data->line == NULL || *data->line == '\0')
		return (0);
	add_history(data->line);
	data->argv = _split(data->line, data);
	if (data->argv == NULL)
		return 1;
	if (builtins())
		return (0);
	if (is_valid_cmd(data, data->argv[0]) != 1)
	{
		printf("\e[31mminishell : %s Command not found\e[0m\n", data->line);
		data->exit_status = 127 << 8;
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(data->program_path, data->argv, NULL);
	return (-1);
}

void	data_init(char **base_env)
{
	t_data	*data;
	char	*value;
	int		i;

	data = data_hook(NULL);
	data->argv = NULL;
	data->line = NULL;
	data->env = NULL;
	data->program_path = NULL;
	data->exit_status = 0;
	data->prompt = get_prompt();
	i = 0;
	while (base_env && base_env[i])
	{
		value = ft_strchr(base_env[i], '=') + 1;
		*(value - 1) = '\0';
		env_export(base_env[i], value, data);
		*(value - 1) = '=';
		i++;
	}
	if (env_grepvalue("PATH") == 0)
		env_export("PATH", get_paths_env(), data);
}

void ex()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	(void)ac;
	(void)av;

	atexit(ex);
	// char **argv;
	// int i = 0;
	// goto here;
	printf("\e[1;1H\e[2J");
	data_hook(&data);
	data_init(env);
	while (1)
	{
		execute();
		waitpid(-1, &data.exit_status, 0);
		free (data.program_path);
		free (data.line);
		free_tab(data.argv);
		data.argv = NULL;
		data.program_path = NULL;
	}
	// here :
	// 	argv = _split("ls $? '$PATH' $PATH", &data);
	// 	i = 0;
	// 	while (argv[i])
	// 		printf("%s\n", argv[i++]);
	return (EXIT_SUCCESS);
}
