/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:39:17 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/03 03:46:21 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int openfile(char *name, int flags)
{
	int fd = open(name, flags, 0666);
	return (fd);
}

void run(int in, int out, char **av)
{
	// if (av == NULL)
	// 	return;
	is_valid_cmd(data_hook(NULL), av[0]);
	char *ppath = data_hook(NULL)->program_path;
	printf("program path : %s, in:%d, out:%d\n", ppath, in, out);
	int pid = fork();
	if (pid == 0)
	{
		if (in != 0)
			dup2(in, 0);
		if (out != 1)
			dup2(out, 1);
		execve(ppath, av, NULL);
	}
	wait(NULL);
}

int	_redirection()
{
	int	i;
	int in = 0;
	int out = 1;
	char **av = NULL;
	t_data	*data;
	char **commands;

	i = 0;
	data = data_hook(NULL);
	commands = data->commands;
	while  (commands[i])
	{
		if (ft_strncmp(commands[i], ">", 2) == 0)
		{
			// if (out != 1)
			// 	close(out);
			out = openfile(commands[++i], O_CREAT | O_RDWR | O_TRUNC);
		}
		else if (ft_strncmp(commands[i], "|", 2) != 0)
		 	av = _realloc(av, _strdup(commands[i]));
		if (_strlen(commands[i], '\0') == 0 || ft_strncmp(commands[i], "|", 2) == 0)
		{
			av = NULL;
			(in != 0) && (close(in), in = 0);
			(out != 1) && (close(out), out = 1);
		}
		i++;
	}
	run(in, out, av);
	(in != 0) && (close(in), in = 0);
	(out != 1) && (close(out), out = 1);
	printf("\n");
	// safe_exit(-1);
	return (0);
}
