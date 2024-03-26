/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/26 00:07:59 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	argument_count(char *str)
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
			if (str[size] == '\"')
				dqt = (dqt == 0);
			size++;
		}
		if (dqt)
			return (0);
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
		if (str[i] != '\"')
			size++;
		i++;
	}
	return (size);
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
	res = NULL;
	i = 0;
	j = 0;
	printf("%zu\n", size);
	while (str[i])
	{
		c = str[i];
		if (ft_strchr( "\"\'", str[i]) == NULL)
		{
			if (str[i] == '$')
				i += set_var(&str[i + 1], &res, NULL);
			else
				i += set_word(&str[i], &res);
		}
		i++;
	}
	return (res);
}
