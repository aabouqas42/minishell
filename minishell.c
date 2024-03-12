/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/12 17:21:47 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void f(int n)
{
	
}

int main(int ac, char **av, char **env)
{
	char	**commands;
	char	**paths;
	char	*cmd;
	int		index;
	paths = ft_split(get_path(env), ':');
	int child_pid;
	char *line;
	signal(SIGQUIT, f);
	int ret;
	while (1)
	{
		line = readline("aabouqas@aabouqas42$ ");
		commands = ft_split(line, ' ');
		index = check_command(paths, commands[0]);
		cmd = ft_strjoin(paths[index], "/");
		cmd = ft_strjoin(cmd, commands[0]);
		free(cmd);
		child_pid = fork();
		if (child_pid == 0)
		{
			int n = execve(cmd, commands, NULL);
			free (line);
		}
		while (waitpid(child_pid, &ret, 0) != -1);
	}
}
