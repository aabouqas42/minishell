/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/18 18:32:50 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins(t_data *data)
{
	if (!ft_strncmp(data->argv[0], "exit", 4) && ft_strlen(data->argv[0]) == 4)
		return (_free(data), exit(0), 1);
	if (!ft_strncmp(data->argv[0], "c", 5) && ft_strlen(data->argv[0]) == 1)
		return (printf("\e[1;1H\e[2J"), 1);
	if (!ft_strncmp(data->argv[0], "cd", 2) && ft_strlen(data->argv[0]) == 2)
		return (cd(data->argv), 1);
	if (!ft_strncmp(data->argv[0], "echo", 4) && ft_strlen(data->argv[0]) == 4)
		return (echo(data->line + ft_strlen(data->argv[0])), 1);
	if (!ft_strncmp(data->argv[0], "pwd", 3) && ft_strlen(data->argv[0]) == 3)
		return (pwd(), 1);
	if (!ft_strncmp(data->argv[0], "export", 6) && ft_strlen(data->argv[0]) == 6)
		return (env_sort(data->_env), 1);
	return (0);
}

int	execute(t_data *data)
{
	int	child_pid;

	data->line = readline(data->prompt);
	if (data->line == NULL || *data->line == '\0')
		return (0);
	add_history(data->line);
	data->argv = _split(data->line);
	if (data->argv == NULL)
		return 1;
	if (builtins(data))
		return (0);
	if (is_valid_cmd(data, data->argv[0]) != 1)
	{
		printf("\033[31mCommand not found : %s\033[0m\n", data->line);
		data->exit_status = 127;
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(data->program_path, data->argv, data->env);
	return (-1);
}

int	main(int ac, char **av, char **env)
{
	char **argv;
	(void)ac;
	(void)av;
	t_data	data;

	data_init(&data, env);
	// goto here;
	while (1)
	{
		execute(&data);
		waitpid(-1, &data.exit_status, 0);
		free (data.program_path);
		free (data.line);
		free_tab(data.argv);
		data.argv = NULL;
		data.program_path = NULL;
	}
	// here :
	// while (1)
	// {
	// 	char *line = readline("$ ");
	// 	add_history(line);
	// 	argv = _split(line);
	// 	int i = 0;
	// 	while (argv && argv[i])
	// 		printf("%s\n", argv[i++]);
	// }
	return (EXIT_SUCCESS);
}
