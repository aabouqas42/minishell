/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:28:12 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/10 09:09:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_arg_free(t_arg *head)
{
	t_arg	*next;

	while (head)
	{
		next = head->next;
		// printf("---[%p]---\n", head->value);
		free (head->value);
		head->value = NULL;
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
