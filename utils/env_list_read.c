/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:17:22 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/18 02:59:56 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_valueof(char *name, t_data	*data)
{
	t_env	*i;

	if (name && data)
	{
		name++;
		i = data->_env;
		// if (*name == '?')
		// 	return (printf("%d", data->exit_status));
		while (i)
		{
			if (!ft_strncmp(i->name, name, ft_strlen(name) +1))
				return (i->value);
			i = i->next;
		}
	}
	return (NULL);
}