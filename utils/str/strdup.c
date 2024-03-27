/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:19:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/27 01:00:28 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*_strdup(char *str)
{
	size_t	i;
	char	*res;

	if (str == NULL)
		return (NULL);
	res = malloc(_strlen(str) + 1);
	if (res == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
