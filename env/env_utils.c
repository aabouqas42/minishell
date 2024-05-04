/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:57:27 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/04 11:16:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_create(char *name, char *value)
{
	t_env	*env;

	if (name == NULL)
		return (NULL);
	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		safe_exit(-1);
	env->name = ft_strdup(name);
	if (value != NULL)
		env->value = ft_strdup(value);
	return (env);
}

void	env_free(t_env *env)
{
	if (env == NULL)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}

void	env_print(t_env	*head)
{
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
}

size_t	env_size(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*env_get_last(t_env	*env)
{
	if (env == NULL)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}
