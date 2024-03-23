/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/23 15:16:30 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_export(t_data *data)
{
	char	*name;
	char	*value;
	size_t	i;

	i = 0;
	if (data == NULL || data->argv == NULL)
		return (0);
	if (data->argv[1] == NULL)
		return (env_print(data->env), 1);
	name = data->argv[1];
	value = "";
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	if (name[i] == '=' && name[i + 1] != '\0')
		value = (name + i + 1);
	name[i] = '\0';
	if (env_export(name, value, data) == ENV_CREATED)
		return (1);
	return (0);
}
