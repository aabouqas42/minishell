/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:43:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/03 16:27:38 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_grepvalue(char *name)
{
	t_data	*data;
	t_env	*env;

	if (name != NULL)
	{
		data = data_hook(NULL);
		env = data->env;
		while (env)
		{
			if (is_same(env->name, name))
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

int	env_export(char *name, char *value)
{
	t_data	*data;
	t_env	*tmp;

	data = data_hook(NULL);
	if (!env_valid_name(name))
		return (0);
	if (data->env == NULL)
	{
		data->env = env_create(name, value);
		return ((data->env != NULL));
	}
	tmp = env_get(name, data);
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = _strdup(value);
		return ((tmp->value != NULL));
	}
	tmp = env_get_last(data->env);
	tmp->next = env_create(name, value);
	return (tmp->next != NULL);
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
	if (is_same(tmp->name, name))
	{
		*env = (*env)->next;
		return (env_free(tmp), 1);
	}
	while (tmp->next)
	{
		if (is_same(tmp->next->name, name))
		{
			todelete = tmp->next;
			tmp->next = tmp->next->next;
			return (env_free(todelete), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	init_env_array(void)
{
	t_data	*data;
	t_env	*env;
	char	*line;
	char	*tmp;

	data = data_hook(NULL);
	data->env_2d = NULL;
	env = data->env;
	while (env)
	{
		line = _strdup(env->name);
		tmp = _strjoin(line, "=");
		line = _strjoin(tmp, env->value);
		data->env_2d = _realloc(data->env_2d, line);
		env = env->next;
	}
}
