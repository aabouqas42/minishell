/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/03 20:23:45 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_export(void)
{
	char	*name;
	char	*value;
	char	*save;
	t_data	*data;
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
		save = _strchr(data->args[i], '=');
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
			free(value);
		} else
			env_export(name, NULL);
		i++;
	}
	return (0);
}
