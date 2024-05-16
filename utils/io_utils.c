/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:46:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/15 19:07:33 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_out(t_cmd *cmd, t_arg **arg)
{
	t_data	*data;
	int		action;

	data = data_hook(NULL);
	action = O_RDWR | O_CREAT;
	if ((*arg)->type == ARG_REDOUT)
		action |= O_TRUNC;
	if ((*arg)->type == ARG_APPEND)
		action |= O_APPEND;
	if (cmd->out > 1)
		close(cmd->out);
	cmd->out = open((*arg)->next->value, action, 0666);
	if (cmd->out == -1)
	{
		do_error(PERMIDEN_ERR, "", (*arg)->next->value);
		exit(1);
	}
	*arg = (*arg)->next;
}

void	set_pipes(t_cmd *cmd, int first, int next)
{
	t_data	*data;

	if (first && !next)
		return ;
	data = data_hook(NULL);
	if (first && next && cmd->out == 1)
		cmd->out = data->fds[1];
	if (!first && next)
	{
		if (cmd->in == 0)
			cmd->in = data->oldfd;
		if (cmd->out == 1)
			cmd->out = data->fds[1];
	}
	if (!first && !next)
	{
		if (cmd->in == 0)
			cmd->in = data->oldfd;
	}
}

void	set_io(t_cmd *cmd)
{
	t_data	*data;

	data = data_hook(NULL);
	if (cmd->out > 1)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close (cmd->out);
	}
	if (cmd->in > 0)
	{
		dup2(cmd->in, STDIN_FILENO);
		close (cmd->in);
	}
	if (data->oldfd > 1)
		close (data->oldfd);
	if (data->fds[0] > 1)
		close (data->fds[0]);
	if (data->fds[1] > 1)
		close (data->fds[1]);
}

int	set_in(t_cmd *cmd, t_arg **arg)
{
	t_arg	*tmp;
	int		fd;

	fd = open((*arg)->next->value, O_RDONLY);
	if (fd == -1)
	{
		cmd->in = fd;
		do_error(NSFODIR_ERR, "", (*arg)->next->value);
		return (0);
	}
	(*arg) = (*arg)->next;
	tmp = *arg;
	while (tmp)
	{
		if (tmp->type == ARG_HERDOC)
			return (1);
		tmp = tmp->next;
	}
	if (cmd->in != 0)
		close(cmd->in);
	cmd->in = fd;
	return (1);
}

int	init_redirections(t_cmd *cmd)
{
	t_arg	*args;

	args = cmd->linked_argv;
	while (args)
	{
		if (args->type == ARG_REDOUT || args->type == ARG_APPEND)
			set_out(cmd, &args);
		else if (args->type == ARG_HERDOC)
			args = args->next;
		else if (args->type == ARG_REDIN)
		{
			if (set_in(cmd, &args) == 0)
				return (0);
		}
		args = args->next;
	}
	return (1);
}
