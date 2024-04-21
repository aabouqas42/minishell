/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_funcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:48:03 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/21 16:45:47 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*_calloc(size_t size)
{
	char	*res;

	res = malloc(size);
	if (res == NULL)
		safe_exit(-1);
	while (size--)
		res[size] = '\0';
	return ((void *)res);
}

size_t	_strlenc(char *str, char c)
{
	size_t	size;

	size = 0;
	while (str && str[size] && str[size] != c)
		size++;
	return (size);
}

char	*_strdup(char *str)
{
	size_t	i;
	char	*res;

	if (str == NULL)
		return (NULL);
	res = malloc(_strlenc(str, '\0') + 1);
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

char	*_strndup(char *str, size_t size)
{
	size_t	i;
	char	*res;

	if (str == NULL)
		return (NULL);
	res = malloc(size + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < size)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
