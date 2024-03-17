/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:43:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/17 02:36:54 by aabouqas         ###   ########.fr       */
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
	env->printed = 0;
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

int	env_export(char *name, char *value, t_env **env)
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
	// printf("------------------\n");
	while (head)
	{
		printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	// printf("------------------\n");
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
	if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
	{
		printf("[ deleting %s ]\n", tmp->name);
		*env = (*env)->next;
		env_memfree(tmp);
		return (1);
	}
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->name, name, ft_strlen(name)) == 0)
		{
			printf("[ deleting %s ]\n", tmp->name);
			todelete = tmp->next;
			tmp->next = tmp->next->next;
			env_memfree(todelete);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
