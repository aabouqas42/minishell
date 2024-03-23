/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/23 08:03:32 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_switcher(int *b, char *str, int size)
{
	if ((ft_strchr("\"\'", str[size]) && str[size - 1] != '\\')
		|| str[size] == '\\')
		*b = (*b == 0);
}

int	argument_count(char *str)
{
	size_t	wc;
	int		size;
	int		dqt;

	wc = 0;
	dqt = 0;
	while (str && *str)
	{
		size = 0;
		while (*str == ' ')
			str++;
		wc += (*str != '\0');
		while (str[size] && (str[size] != ' ' || dqt == 1))
		{
			ft_switcher(&dqt, str, size);
			size++;
		}
		if (dqt)
			return (-1);
		str += size;
	}
	return (wc);
}

size_t	get_size(char *str, int n)
{
	size_t	size;
	int		i;
	char	c;

	i = 0;
	size = 0;
	while (str[i] && i < n)
	{
		c = str[i];
		if (!ft_strchr("\"\'\\", c)
			|| (ft_strchr("\"\'\\", c) && str[i - 1] == '\\'))
			size++;
		i += (str[i - 1] == '\\');
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

char	*ft_strndup(char *str, size_t n)
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
	res = malloc(size + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		c = str[i];
		if (!ft_strchr("\"\'\\", c)
			|| (ft_strchr("\"\'\\", c) && str[i - 1] == '\\') )
				res[j++] = c;
		i += (str[i - 1] == '\\');
		i++;
	}
	return (res[j] = '\0', res);
}
