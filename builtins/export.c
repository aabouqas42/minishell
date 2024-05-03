/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/03 10:04:03 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_export()
{
	char	*name;
	char	*value;
	char	*save;
	t_data *data;
	size_t	i;

	data = data_hook(NULL);
	if (data == NULL || data->args == NULL)
		return (0);
	if (data->args[1] == NULL || is_io_op(data->args[1]))
		return (env_sort(data->env), 1);
	i = 1;
	value = "";
	while (data->args[i])
	{
		name = data->args[i];
		save = ft_strchr(data->args[i], '=');
		if (save)
		{
			if (*(save -1) == '+')
			{
				*(save -1) = '\0';
				value = env_grepvalue(name);
			}
			*(save++) = '\0';
			value = ft_strjoin(value, save);
			env_export(name, value);
			// this fixed the leaks :)
			free(value);
		} else
			env_export(name, NULL);
		i++;
	}
	// if (i == 0)
	// 	return (env_sort(data->env), 0);

	// name = data->args[1];
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
