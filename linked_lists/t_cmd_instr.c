/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:38:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/05 19:30:34 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_cmd_add(t_cmd to_add)
{
	t_data	*data;
	t_cmd	*end;

	data = data_hook(NULL);
	if (to_add._argv == NULL)
		return;
	end = data->cmds;
	if (end == NULL)
	{
		data->cmds = _calloc(sizeof(t_cmd));
		data->cmds->_argv = to_add._argv;
		data->cmds->in = to_add.in;
		data->cmds->out = to_add.out;
		data->cmds->heredocs = to_add.heredocs;
		return;
	}
	while (end->next)
		end = end->next;
	end->next = _calloc(sizeof(t_cmd));
	end->next->_argv = to_add._argv;
	end->next->in = to_add.in;
	end->next->out = to_add.out;
	data->cmds->heredocs = to_add.heredocs;
}
