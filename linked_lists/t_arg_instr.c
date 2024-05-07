/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:38:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/07 20:09:33 by mait-elk         ###   ########.fr       */
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
	end = data->args;
	if (end == NULL)
	{
		data->args = _calloc(sizeof(t_arg));
		data->args->value = value;
		data->args->type = type;
		return;
	}
	while (end->next)
		end = end->next;
	end->next = _calloc(sizeof(t_arg));
	end->next->value = value;
	end->next->type = type;
}

void	t_arg_put(char *value, t_arg_type type, t_arg **head)
{
	t_arg	*end;

	if (value == NULL || head == NULL)
		return;
	end = *head;
	if (end == NULL)
	{
		(*head) = _calloc(sizeof(t_arg));
		(*head)->value = value;
		(*head)->type = type;
		return;
	}
	while (end->next)
		end = end->next;
	end->next = _calloc(sizeof(t_arg));
	end->next->value = value;
	end->next->type = type;
}

// void	t_arg_insert(char *value, t_arg_type type, t_arg **head)
// {
	
// }