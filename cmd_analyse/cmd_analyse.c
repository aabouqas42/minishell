/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analyse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:07:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/22 19:54:55 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_heredoc(char *target)
{
	t_data	*data;

	data = data_hook(NULL);
	while (1)
	{
		char	*in = readline("heredoc > ");
		if (in && is_same(in, target))
			break;
		data->heredoc = _strjoin(data->heredoc, in);
		data->heredoc = _strjoin(data->heredoc, "\n");
	}
}

void	set_out(char **arg)
{
	t_data	*data;
	int		action;

	data = data_hook(NULL);
	action = O_RDWR | O_CREAT;
	if (is_same(*arg, ">"))
		action |= O_TRUNC;
	if (is_same(*arg, ">>"))
		action |= O_APPEND;
	if (data->out > 1)
		close(data->out);
	data->out = open(*(arg + 1), action, 0666);
	if (data->out == -1)
		perror("open");
}

void	set_pipes(int first, int there_is_next)
{
	t_data	*data;

	data = data_hook(NULL);
	if (first && there_is_next)
		dup2(data->fds[1], 1);
	if (!first && there_is_next)
	{
		dup2(data->oldfd, 0);
		dup2(data->fds[1], 1);
	}
	if (!first && !there_is_next)
		dup2(data->oldfd, 0);
	if (there_is_next)
	{
		close (data->fds[0]);
		close (data->fds[1]);
		close(data->oldfd);
	}
}

void	set_in_out()
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->out != 1)
	{
		dup2(data->out, STDOUT_FILENO);
		close (data->out);
	}
	if (data->in != 0)
	{
		dup2(data->in, STDIN_FILENO);
		close (data->in);
	}
}

char	**get_argv(char **args)
{
	t_data	*data;
	char	**argv;

	data = data_hook(NULL);
	argv = NULL;
	while (*args)
	{
		if (is_same(*args, ">") || is_same(*args, ">>"))
		{
			set_out(args);
			args += 1;
		} else if (is_same(*args, "<<"))
		{
			open_heredoc(*(args + 1));
			printf("%s\n", data->heredoc);
		} else if (is_same(*args, "<"))
		{
			args++;
			data->in = open(*args, O_RDONLY);
		} else
			argv = _realloc(argv, *args);
		args++;
	}
	return (argv);
}
