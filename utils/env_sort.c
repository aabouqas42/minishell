/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:25:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/17 03:57:16 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	all_done(t_env *env)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (env)
	{
		i += (env->printed == 1);
		size++;
		env = env->next;
	}
	return (i == size);
}

void	rest(t_env *env)
{
	while (env)
	{
		env->printed = 0;
		env = env->next;
	}
}

void	env_sort(t_env *env)
{
	t_env	*temp;
	t_env	*small;
	char	c;

	while (all_done(env) == 0)
	{
		temp = env;
		c = 127;
		while (temp)
		{
			if (*temp->name <= c && temp->printed == 0)
			{
				small = temp;
				c = *temp->name;
			}
			temp = temp->next;
		}
		if (small && small->printed != 1)
			printf("%s=%s\n", small->name, small->value);
		small->printed = 1;
	}
	rest(env);
}
