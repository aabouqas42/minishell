/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:43:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/18 09:04:50 by mait-elk         ###   ########.fr       */
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
	t_data *data;
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
		tmp->value = p_strdup(value);
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

char	**env_to_2darray()
{
	char	**res;
	t_env	*env;
	char	*tmp;
	char	*line;
	int		i;
	int		j;

	i = 0;
	res = NULL;
	env = data_hook(NULL)->env;
	while (env)
	{
		i++;
		env = env->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (res == NULL)
		safe_exit(-1);
	env = data_hook(NULL)->env;
	j = 0;
	while (j < i)
	{
		line = NULL;
		tmp = ft_strjoin(line, env->name);
		free(line);
		line = ft_strjoin(tmp, "=");
		free(tmp);
		tmp = ft_strjoin(line, env->value);
		free(line);
		res[j] = tmp;
		// printf("%s\n", res[j]);
		j++;
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}
