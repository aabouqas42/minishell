/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:39:05 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/29 01:54:29 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_env(t_env *head)
{
	t_env	*curr;

	while (head)
	{
		curr = head->next;
		free (head->name);
		free (head->value);
	}
	return (0);
}