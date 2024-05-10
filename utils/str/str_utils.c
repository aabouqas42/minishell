/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:57:39 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/10 18:00:07 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	_strlen(char *str)
{
	return (_strlenc(str, 0));
}

int	is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*_strnjoin(char *str1, char *str2, size_t size)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = _nsx_strlen(str1) + size;
	str = malloc (len + 1);
	if (str == NULL)
		return (free (str1), safe_exit(-1), NULL);
	i = 0;
	while (str1 && str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (str2 && *str2 && size)
	{
		str[i] = *str2;
		i++;
		str2++;
		size--;
	}
	str[i] = '\0';
	return (free (str1), str);
}

char	*_strjoin(char *str1, char *str2)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = _strlen(str1) + _strlen(str2);
	str = malloc (len + 1);
	if (str == NULL)
		return (free (str1), safe_exit(-1), NULL);
	i = 0;
	while (str1 && str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (str2 && *str2)
	{
		str[i] = *str2;
		i++;
		str2++;
	}
	str[i] = '\0';
	return (free (str1), str);
}

char	*_strchr(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}
