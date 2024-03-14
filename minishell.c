/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/14 14:49:06 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*get_username(char **env)
{
	char	*uname;

	uname = getenv("USER");
	if (uname)
		return (uname);
	return ("mait-aabouqas");
}

int	buildins(char **cmd, char *line)
{
	if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (exit(0), 1);
	if (ft_strncmp(cmd[0], "clear", 5) == 0 && ft_strlen(cmd[0]) == 5)
		return (printf("\e[1;1H\e[2J"), 1);
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		return (cd(cmd[1]), 1);
	if (ft_strncmp(cmd[0], "echo", 5) == 0 && ft_strlen(cmd[0]) == 5)
		return (echo(line + ft_strlen(cmd[0])), 1);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (pwd(), 1);
	return (0);
}

int	execute(t_data *data)
{
	int		child_pid;

	data->line = readline(data->promte);
	if (data->line == NULL || *data->line == '\0')
		return (0);
	add_history(data->line);
	data->argv = ft_split(data->line, ' ');
	if (buildins(data->argv, data->line))
		return (1);
	if (is_valid_cmd(data, data->argv[0]) != 1)
	{
		printf("\033[31mCommand not found : %s\033[0m\n", data->line);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(data->program_path, data->argv, data->env);
	return (-1);
}

void f(int s)
{
	(void)s;
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	data_init(&data, env);
	while (1)
	{
		execute(&data);
		waitpid(-1, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
