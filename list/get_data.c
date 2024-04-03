/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:51:00 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/03 00:54:50 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list_args	*get_last(t_list_args *head)
{
	t_list_args	*last_node;

	if (head == NULL)
		return (NULL);
	last_node = head;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

t_list_args	*get_first()
{
	return (data_hook(NULL)->list);
}

