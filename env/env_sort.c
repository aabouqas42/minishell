/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:25:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 11:54:41 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_val(char *name, char *value)
{
	if (value)
	{
		print(STDOUT_FILENO, name, 0);
		print(STDOUT_FILENO, "=\"", 0);
		print(STDOUT_FILENO, value, 0);
		print(STDOUT_FILENO, "\"", 1);
	}
	else
		print(STDOUT_FILENO, name, 1);
}

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
			{
				print(STDOUT_FILENO, "declare -x ", 0);
				print_val(temp->name, temp->value);
			}
			temp = temp->next;
		}
		c++;
	}
}
