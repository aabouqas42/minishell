/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:43:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/19 18:35:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_export(char *name, char *value, t_env **env)
{
	t_env	*tmp;

	if (name == NULL || value == NULL || env == NULL)
		return (ENV_NOT_CREATED);
	if (*env == NULL)
	{
		*env = env_create(name, value);
		if (*env == NULL)
			return (ENV_FAILURE);
		return (ENV_CREATED);
	}
	tmp = *env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) +1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup((const char *)value);
			if (tmp->value == NULL)
				return (ENV_FAILURE);
			return (ENV_CREATED);
		}
		tmp = tmp->next;
	}
	tmp->next = env_create(name, value);
	if (tmp->next == NULL)
		return (ENV_FAILURE);
	return (ENV_CREATED);
}

int	env_unset(char *name, t_env **env)
{
	t_env	*todelete;
	t_env	*tmp;

	if (name == NULL || env == NULL)
		return (0);
	tmp = *env;
	if (tmp == NULL)
		return (1);
	if (ft_strncmp(tmp->name, name, ft_strlen(name) +1) == 0)
	{
		*env = (*env)->next;
		return (env_free(tmp), 1);
	}
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->name, name, ft_strlen(name) +1) == 0)
		{
			todelete = tmp->next;
			tmp->next = tmp->next->next;
			return (env_free(todelete), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
