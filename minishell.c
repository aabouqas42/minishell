/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/13 03:33:06 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*get_username(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "USER=", ft_strlen(env[i])))
			return (env[i] + 5);
		i++;
	}
	return ("mait-aabouqas");
}

int	buildins(char **cmd, char *line)
{
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
	if (fork() == 0)
		execve(program_path, cmd, NULL);
	free (line);
	free_2darray(cmd);
	return (-1);
}

int	main(int ac, char **av, char **env)
{
	while (1)
	{
		execute(env);
		waitpid(-1, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
