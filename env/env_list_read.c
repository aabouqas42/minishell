/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:17:22 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/22 05:36:51 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_get(char *name, t_data	*data)
{
	t_env	*i;

	if (name && data && *name != '\0')
	{
		// name++; COMMENTED CAUSE I HAVE PROBLEM IN EXPORT COMMAND TO CREATE ANOTHER ENV WITH SAME NAME HE CANNOT FOUND THE NAME BECAUSE THIS LINE SKIPPED FIRST CHARACTER !
		i = data->_env;
		while (i)
		{
			if (ft_strncmp(i->name, name, ft_strlen(name) +1) == 0)
				return (i);
			i = i->next;
		}
	}
	return (NULL);
}
