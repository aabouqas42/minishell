/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:13:57 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/16 12:14:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_heredoc(t_cmd *cmd, t_arg *target)
{
	if (cmd->in != 0)
	{
		close(cmd->in);
		cmd->in = 0;
	}
	cmd->in = open_heredoc(target);
}

static int	stdin_closed(t_cmd cmd)
{
	if (read(0, NULL, 0) == -1)
	{
		while (cmd.linked_argv)
		{
			free(cmd.linked_argv);
			cmd.linked_argv = cmd.linked_argv->next;
		}
		cmd.linked_argv = NULL;
		if (cmd.in != 0)
			close(cmd.in);
		return (1);
	}
	return (0);
}

int	get_commands(t_arg *args)
{
	t_cmd	cmd;

	data_hook(NULL)->exit_status = 0;
	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.out = 1;
	while (args)
	{
		while (args && args->type != ARG_PIPE)
		{
			if (stdin_closed(cmd))
				return (0);
			data_hook(NULL)->fix_doubleprt = 2;
			if (args->type == ARG_HERDOC && args->next)
				create_heredoc(&cmd, args->next);
			t_arg_put(args->value, args->type, &cmd.linked_argv);
			data_hook(NULL)->fix_doubleprt = 1;
			args = args->next;
		}
		(init_clear_argv(&cmd), t_cmd_add(cmd));
		ft_bzero(&cmd, sizeof(t_cmd));
		cmd.out = 1;
		if (args)
			args = args->next;
	}
	return (1);
}
