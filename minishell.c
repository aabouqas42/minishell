/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/19 23:08:53 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins(t_data *data)
{
	if (!ft_strncmp(data->argv[0], "exit", 5))
		return (_free(data), exit(0), 1);
	if (!ft_strncmp(data->argv[0], "clear", 6))
		return (printf("\e[1;1H\e[2J"), 1);
	if (!ft_strncmp(data->argv[0], "cd", 3))
		return (cd(data->argv), 1);
	if (!ft_strncmp(data->argv[0], "echo", 5))
		return (echo(data), 1);
	if (!ft_strncmp(data->argv[0], "pwd", 4))
		return (pwd(), 1);
	if (!ft_strncmp(data->argv[0], "export", 7))
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
		printf("\e[31mminishell : %s Command not found\e[0m\n", data->line);
		data->exit_status = 127 << 8;
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

	printf("\e[1;1H\e[2J");
	data_init(&data, env);
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
	return (EXIT_SUCCESS);
}
