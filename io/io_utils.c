/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:46:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 18:08:53 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_out(char **arg)
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
	return (1);
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
	if (data->oldfd > 1)
		close (data->oldfd);
	if (data->fds[0] > 1)
		close (data->fds[0]);
	if (data->fds[1] > 1)
		close (data->fds[1]);
}

int	set_in(t_data	*data, char *file_name)
{
	if (data->in != 0)
		close(data->in);
	data->in = open(file_name, O_RDONLY);
	if (data->in == -1)
	{
		do_error(NSFODIR_ERR, file_name);
		safe_exit(-1);
	}
	return (1);
}

char	**get_argv(char **args)
{
	t_data	*d;
	char	**argv;
	int		i;

	d = data_hook(NULL);
	argv = NULL;
	i = 0;
	while (args[i])
	{
		if (d->flags[i].is_io_op && (is_same(args[i], ">") || is_same(args[i], ">>")))
			i += set_out(args + i);
		else if (d->flags[i].is_io_op && is_same(args[i], "<<"))
		{
			i++;
			print(2, args[i], 1);
			open_heredoc((args[i]));
		}
		else if (is_same(args[i], "<"))
			i += set_in(d, args[i + 1]);
		else
			argv = _realloc(argv, args[i]);
		i++;
	}
	return (argv);
}
