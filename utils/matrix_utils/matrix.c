/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:34:25 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/12 11:43:14 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_heredoc(t_cmd *cmd, t_arg *target)
{
	if (cmd->in != 0)
	{
		close(cmd->in);
		cmd->in = 0;
	}
	cmd->in = open_heredoc(target);
}

// static int	is_tty(int in)
// {
// 	if (!isatty(0))
// 	{
// 		if (in != 0)
// 			close(in);
// 		return (0);
// 	}
// 	return (1);
// }

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
			// if (is_tty(cmd.in) == 0)
			// 	return (0);
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
