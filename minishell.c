/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/13 15:25:04 by mait-elk         ###   ########.fr       */
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
	if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (exit(0), 1);
	if (ft_strncmp(cmd[0], "clear", 5) == 0)
		return (printf("\e[1;1H\e[2J"), 1);
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return (cd(cmd[1]), 1);
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (echo(line + ft_strlen(cmd[0])), 1);
	return (0);
}

int	execute(char **env)
{
	char	*program_path;
	char	**cmd;
	char	*line;
	int		child_pid;

	printf("%s@1337 $ ", get_username(env));
	line = readline(NULL);
	if (line == NULL || *line == '\0')
		return (free(line), 0);
	cmd = ft_split(line, ' ');
	if (buildins(cmd, line))
		return (free (line), free_2darray(cmd), 1);
	if (is_valid_cmd(env, cmd[0], &program_path) != CMD_VALID)
	{
		printf("\033[31mCommand not found : %s\033[0m\n", line);
		free (line);
		free_2darray(cmd);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(program_path, cmd, env);
	free (line);
	free_2darray(cmd);
	return (-1);
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
