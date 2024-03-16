/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:43:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/16 02:51:15 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static t_env	*env_create(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->name = ft_strdup(name);
	if (env->name == NULL)
		return (NULL);
	env->value = ft_strdup(value);
	if (env->value == NULL)
		return (free(env->name), NULL);
	env->next = NULL;
	return (env);
}

void	env_memfree(t_env *env)
{
	if (env == NULL)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}

int	env_add(char *name, char *value, t_env **env)
{
	t_env	*tmp;

	if (name == NULL || value == NULL || env == NULL)
		return (0);
	if (*env == NULL)
	{
		*env = env_create(name, value);
		return (*env != NULL);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = env_create(name, value);
	return (tmp->next != NULL);
}

void	env_print(t_env	*head)
{
	while (head)
	{
		printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
}