/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:48:03 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/16 11:54:47 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	_str_n_equal(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
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
		safe_exit(-1);
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
