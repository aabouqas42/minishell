/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:38:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/05 13:01:06 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_arg_add(char *value, t_arg_type type)
{
	t_data	*data;
	t_arg	*end;

	data = data_hook(NULL);
	if (value == NULL)
		return;
	end = data->_args;
	if (end == NULL)
	{
		data->_args = _calloc(sizeof(t_arg));
		data->_args->value = value;
		data->_args->type = type;
		return;
	}
	while (end->next)
		end = end->next;
	end->next = _calloc(sizeof(t_arg));
	end->next->value = value;
	end->next->type = type;
}
