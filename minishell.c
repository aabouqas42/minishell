/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:38:31 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/11 18:50:58 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int ac, char **av, char **env)
{
	char	**commands;
	char	**paths;
	char	*cmd;
	int		index;
	// while (env[i])
		// printf("%s\n", env[i++]);
	// printf("%s\n", env[4]);
	paths = ft_split(env[4] + 5, ':');
	// int i = 0;
	// while (paths[i])
	// 	printf("[%s]\n", paths[i++]);
	// char *argv[] = {"ls", "-l", NULL};
	// printf("%d\n", n);
	// execv("/bin/ls", argv);
	// int check;
	while (1)
	{
		char *line = readline("$ ");
		commands = ft_split(line, ' ');
		index = check_command(paths, commands[0]);
		if (index != 0)
			errexit("command not found\n", NULL);
		cmd = ft_strjoin(paths[index], ft_strjoin("/", commands[0]));
		// printf("[%s]\n", commands[0]);
		// paths[0] -= 4;
		char *envp[] = { "PATH=/usr/bin", NULL };
		int n = execve(cmd, commands, envp);
		printf("[%d %s]\n", n, cmd);
		free (line);
		free (cmd);
	}
}
