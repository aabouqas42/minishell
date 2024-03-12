/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:38:31 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/12 12:16:03 by aabouqas         ###   ########.fr       */
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
	// char *argv[] = {"ls", "-l", NULL};
	// printf("%d\n", n);
	// execv("/bin/ls", argv);
	// int check;
	// int e = access("/usr/local/bin/ls", X_OK);
	// printf("%d\n", e);
	// exit(0);
	int child_pid;
	char *line;
	line = readline("aabouqas@aabouqas42$ ");
	while (1)
	{
		commands = ft_split(line, ' ');
		index = check_command(paths, commands[0]);
		if (index == -1)
			errexit("command not found\n", NULL);
		cmd = ft_strjoin(paths[index], "/");
		cmd = ft_strjoin(cmd, commands[0]);
		free(cmd);
		char *envp[] = { "PATH=/usr/bin", NULL };
		child_pid = fork();
		if (child_pid == 0)
		{
			int n = execve(cmd, commands, envp);
			free (line);
			free (cmd);
		}
		while (waitpid(child_pid, NULL, 0) != -1);
		line = readline("aabouqas@aabouqas42$ ");
	}
}
