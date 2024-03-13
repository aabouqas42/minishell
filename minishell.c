/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/13 02:21:59 by aabouqas         ###   ########.fr       */
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
	return ("minishell");
}

int	execute(char **env)
{
	char	*program_path;
	char	**cmd;
	char	*line;
	int		child_pid;

	line = readline("%s@1337$ ", get_username(env));
	cmd = ft_split(line, ' ');
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
	{
		cd(cmd[1]);
		return (0);
	}
	if (is_valid_cmd(env, cmd[0], &program_path) == CMD_FAIL)
	{
		free (line);
		free_2darray(cmd);
		printf("Command not found\n");
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(program_path, cmd, NULL);
	free (line);
	free_2darray(cmd);
	return (child_pid);
}

int	main(int ac, char **av, char **env)
{
	while (1)
		waitpid(execute(env), NULL, 0);
	return (EXIT_SUCCESS);
}
