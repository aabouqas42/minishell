/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/13 22:59:13 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
	return (0);
}

int	execute(char **env)
{
	char	*program_path;
	char	**argv;
	char	*line;
	int		child_pid;

	line = readline("$ > ");
	if (line == NULL || *line == '\0')
		return (free(line), 0);
	add_history(line);
	argv = ft_split(line, ' ');
	if (buildins(argv, line))
		return (free (line), free_2darray(argv), 1);
	if (is_valid_cmd(argv[0], &program_path) != CMD_VALID)
	{
		printf("\033[31mCommand not found : %s\033[0m\n", line);
		free (line);
		free_2darray(argv);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		argv++;
		// printf("<%s %s>\n", program_path, *cmd);
		execve(program_path, argv, env);
	}
	free (line);
	free_2darray(argv);
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
	while (1)
	{
		execute(env);
		waitpid(-1, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
