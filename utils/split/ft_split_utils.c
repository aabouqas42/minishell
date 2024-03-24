/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/24 22:02:32 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*
	NEED TO REMOVE EMPTY STRINGS , DON'T ALLOCATE IT <IF ITS EMPTY STRING ONLY>
*/
size_t	argument_count(char *str)
{
	size_t	wc;
	int		i;
	int		dqt;

	wc = 0;
	dqt = 0;
	while (str && *str)
	{
		i = 0;
		while (*str && *str == ' ')
			str++;
		wc += (*str != '\0');
		while (str[i] && (str[i] != ' ' || dqt == 1))
		{
			if (str[i] == '\"')
				dqt = (dqt == 0);
			i++;
		}
		if (dqt)
			return (0);
		str += i;
	}
	return (wc);
}

size_t	get_size(char *str, int n)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	while (str[i] && i < n)
	{
		if (str[i] != '\"')
			size++;
		i++;
	}
	return (size);
}

char	*_strjoin(char *str1, char *str2)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = _nsx_strlen(str1) + _nsx_strlen(str2);
	str = malloc (len + 1);
	if (str == NULL)
		return (free (str1), NULL);
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

char	*_strndup(char *str, size_t n)
{
	size_t	i;
	size_t	size;
	size_t	j;
	char	c;
	char	*res;

	if (str == NULL)
		return (NULL);
	i = 0;
	size = get_size(str, n);
	printf("size to allocating : <%zu>, string :<%s>\n", size, str);
	res = malloc(size + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		c = str[i];
		if (str[i] != '\"')
			res[j++] = c;
		i++;
	}
	res[j] = '\0';
	return (res);
}
