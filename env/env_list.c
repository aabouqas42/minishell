/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:43:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/23 15:28:49 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *env_grepvalue(char *name)
{
	t_data	*data;
	t_env	*env;

	data = data_hook(NULL);
	if (name != NULL && data != NULL)
	{
		env = data->env;
		while (env)
		{
			if (_strcmp(env->name, name) == 0)
				return (env->value);
			env = env->next;
		}
	}
	return (NULL);
}

int	env_valid_name(char *name)
{
	if (name == NULL)
		return (0);
	if (ft_strnstr("if then else elif fi case esac for while \
		until do done in function select", name, ft_strlen(name)))
		return (0);
	if (ft_isdigit(name[0]))
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

int	env_export(char *name, char *value, t_data *data)
{
	t_env	*tmp;

	if (env_valid_name(name) == 0)
		return (ENV_NOT_CREATED);
	if (data->env == NULL)
	{
		data->env = env_create(name, value);
		if (data->env == NULL)
			return (ENV_FAILURE);
		return (ENV_CREATED);
	}
	tmp = env_get(name, data);
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = _strdup(value);
		if (tmp->value == NULL)
			return (ENV_FAILURE);
		return (ENV_CREATED);
	}
	tmp = env_get_last(data->env);
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
	if (_strcmp(tmp->name, name) == 0)
	{
		*env = (*env)->next;
		return (env_free(tmp), 1);
	}
	while (tmp->next)
	{
		if (_strcmp(tmp->next->name, name) == 0)
		{
			todelete = tmp->next;
			tmp->next = tmp->next->next;
			return (env_free(todelete), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
