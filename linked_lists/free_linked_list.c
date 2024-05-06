/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:28:12 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/06 20:30:02 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_arg_free(t_arg *head)
{
	t_arg	*next;

	while (head)
	{
		next = head->next;
		free (head->value);
		free (head);
		head = next;
	}
}

void	t_cmd_free(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		t_arg_free(head->linked_argv);
		free (head);
		head = next;
	}
}
