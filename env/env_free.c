/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:32:40 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/30 18:36:22 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_free_list(t_env *env)
{
	t_env	*curr;

	while (env)
	{
		curr = env->next;
		env_free(env);
		env = curr;
	}
}
