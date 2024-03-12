/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/12 17:52:10 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void f(int n)
{
	
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	**paths;
	char	*cmd;
	char	**commands;
	char	*line;
	int		index;
	int		child_pid;
	int		ret;
	while (*env)
	{
		line = readline("aabouqas@aabouqas42$ ");
		commands = ft_split(line, ' ');
		index = is_valid_cmd(env, commands[0], &cmd);
		printf("[%s]\n", cmd);
		child_pid = fork();
		if (child_pid == 0)
		{
			int n = execve(cmd, commands, NULL);
			free (line);
		}
		while (waitpid(child_pid, &ret, 0) != -1);
	}
	return (EXIT_SUCCESS);
}
