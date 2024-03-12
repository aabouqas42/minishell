/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/12 18:09:29 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	**paths;
	char	*cmd;
	char	**commands;
	char	*line;
	int		child_pid;
	while (1)
	{
		line = readline("aabouqas@1337$ ");
		commands = ft_split(line, ' ');
		if (is_valid_cmd(env, commands[0], &cmd) != CMD_VALID)
		{
			printf("Command not found\n");
			continue ;
		}
		child_pid = fork();
		if (child_pid == 0)
			execve(cmd, commands, NULL);
		while (waitpid(child_pid, NULL, 0) != -1);
		free (line);
	}
	return (EXIT_SUCCESS);
}
