/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:25:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/17 15:35:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_sort(t_env *env)
{
	t_env	*temp;
	char	c;

	c = 0;
	while (c != 127)
	{
		temp = env;
		while (temp)
		{
			if (*temp->name == c)
				printf("%s=%s\n", temp->name, temp->value);
			temp = temp->next;
		}
		c++;
	}
}
