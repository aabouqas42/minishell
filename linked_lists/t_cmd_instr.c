/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:38:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 09:13:41 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_cmd_add(t_cmd to_add)
{
	t_data	*data;
	t_cmd	*end;

	data = data_hook(NULL);
	end = data->cmds;
	if (end == NULL)
	{
		data->cmds = _calloc(sizeof(t_cmd));
		data->cmds->linked_argv = to_add.linked_argv;
		data->cmds->argv = to_add.argv;
		data->cmds->in = to_add.in;
		data->cmds->out = to_add.out;
		return ;
	}
	while (end->next)
		end = end->next;
	end->next = _calloc(sizeof(t_cmd));
	end->next->linked_argv = to_add.linked_argv;
	end->next->argv = to_add.argv;
	end->next->in = to_add.in;
	end->next->out = to_add.out;
}

t_cmd	*t_cmd_get_last(t_cmd *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}