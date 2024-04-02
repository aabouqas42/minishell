/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/31 03:02:04 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export()
{
	char	*name;
	char	*value;
	char	*save;
	t_data *data;
	size_t	i;

	data = data_hook(NULL);
	if (data == NULL || data->commands == NULL)
		return (0);
	i = 1;
	value = "";
	while (data->commands[i])
	{
		name = data->commands[i];
		save = ft_strchr(data->commands[i], '=');
		if (save)
		{
			if (*(save -1) == '+')
			{
				*(save -1) = '\0';
				value = env_grepvalue(name);
			}
			*(save++) = '\0';
			value = ft_strjoin(value, save);
			// printf("name = %s, value = %s\n", name, value);
			env_export(name, value);
		}else
			env_export(name, NULL);
		i++;
	}
	if (i == 0)
		return (env_sort(data->env), 0);
	// if (data->commands[1] == NULL)
	// 	return (env_sort(data->env), 1);
	// name = data->commands[1];
	// value = "";
	// i = 0;
	// if (ft_strchr(name, '='))

	// while (name[i] && name[i] != '=')
	// 	i++;
	// if (name[i] == '=')
	// 	value = (name + i + 1);
	// name[i] = '\0';
	// if (env_export(name, value))
	// 	return (1);
	// return (printf("minishell: export: `%s=%s': not a valid identifier\n", name, value), 0);
	return (0);
}
