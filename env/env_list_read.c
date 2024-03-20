/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:17:22 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/20 01:25:57 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_get(char *name, t_data	*data)
{
	t_env	*i;

	if (name && data && *name != '\0')
	{
		name++;
		i = data->_env;
		// if (*name == '?')
		// {
		// 	printf("%d", data->exit_status >> 8);
		// 	data->exit_status = 0;
		// 	return ;
		// }
		while (i)
		{
			if (ft_strncmp(i->name, name, ft_strlen(name) +1) == 0)
				return (i);
			i = i->next;
		}
	}
	return (NULL);
}
