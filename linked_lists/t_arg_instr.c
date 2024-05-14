/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:38:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/14 16:26:16 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_arg_add(char *value, t_arg_type type)
{
	t_data	*data;
	t_arg	*end;

	data = data_hook(NULL);
	if (value == NULL)
		return ;
	end = data->args;
	if (end == NULL)
	{
		data->args = _calloc(sizeof(t_arg));
		data->args->value = value;
		data->args->type = type;
		return ;
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
		return ;
	end = *head;
	if (end == NULL)
	{
		(*head) = _calloc(sizeof(t_arg));
		(*head)->value = value;
		(*head)->type = type;
		return ;
	}
	while (end->next)
		end = end->next;
	end->next = _calloc(sizeof(t_arg));
	end->next->value = value;
	end->next->type = type;
}

t_arg	*t_arg_get_last(t_arg *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

size_t	t_arg_size(t_arg *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

// void	t_arg_move_to(t_arg **src, t_arg **dest)
// {
// 	t_arg	*src_tmp;
// 	t_arg	*tmp;

// 	if (src == NULL || *src == NULL || dest == NULL)
// 		return ;
// 	src_tmp = *src;
// 	while (src_tmp)
// 	{
// 		tmp = src_tmp->next;
// 		t_arg_put(src_tmp->value, src_tmp->type, dest);
// 		free(src_tmp);
// 		src_tmp = tmp;
// 	}
// 	*src = NULL;
// }
