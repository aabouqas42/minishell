/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:47:45 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/17 15:35:43 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	env_size(t_env *env_head)
{
	size_t	i;

	i = 0;
	while (env_head)
	{
		i++;
		env_head = env_head->next;
	}
	return (i);
}
