/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:46:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/03 10:05:18 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_heredoc(char *target)
{
	t_data	*data;
	char	*in;

	data = data_hook(NULL);
	while (1)
	{
		in = readline("heredoc > ");
		if (in && is_same(in, target))
			break ;
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
		exit(-1);
}

void	set_pipes(int first, int there_is_next)
{
	t_data	*data;

	if (first && !there_is_next)
		return ;
	data = data_hook(NULL);
	if (first && there_is_next && data->out == 1)
		data->out = data->fds[1];
	if (!first && there_is_next)
	{
		if (data->in == 0)
			data->in = data->oldfd;
		if (data->out == 1)
			data->out = data->fds[1];
	}
	if (!first && !there_is_next)
	{
		if (data->in == 0)
			data->in = data->oldfd;
	}
}

void	set_io(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->out > 1)
	{
		dup2(data->out, STDOUT_FILENO);
		close (data->out);
	}
	if (data->in > 0)
	{
		dup2(data->in, STDIN_FILENO);
		close (data->in);
	}
	printf("%d - %d\n", data->oldfd, data->fds[0]);
	if (data->oldfd)
		close (data->oldfd);
	if (data->fds[0])
		close (data->fds[0]);
	if (data->fds[1])
		close (data->fds[1]);
}

char	**get_argv(char **args)
{
	t_data	*data;
	char	**argv;
	int		i;

	data = data_hook(NULL);
	argv = NULL;
	i = 0;
	while (args[i])
	{
		printf("---[%s]---\n", args[i]);
		if (data->flags[i] == FLAG_IO_OP && (is_same(args[i], ">") || is_same(args[i], ">>")))
		{
			set_out(args + i);
			i += 1;
		} else if (is_same(args[i], "<<"))
		{
			open_heredoc((args[i + 1]));
		} else if (is_same(args[i], "<"))
		{
			if (data->in != 0)
				close(data->in);
			data->in = open(args[++i], O_RDONLY);
			if (data->in == -1)
				(do_error(NSFODIR_ERR, args[i]), safe_exit(-1));
		} else
			argv = _realloc(argv, args[i]);
		i++;
	}
	return (argv);
}
