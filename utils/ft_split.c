/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/17 15:35:16 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	size_t	i;
	char	*res;

	res = malloc(n + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		res[i] = s1[i]; 
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	wrdc(char *str)
{
	int size;
	int i;

	size = 0;
	i = 0;
	while (str && *str)
	{
		while (*str == ' ')
			str++;
		if (*str == '"')
		{
			str = ft_strchr(str + 1, '"') + 1;
			size++;
			continue;
		}
		while (str && *str && *str != ' ' && *str != '"')
			str++;
		size++;
	}
	return (size);
}

char	*_getline(char *str)
{
	char	*line;
	int		i;
	int		size;

	size = 0;
	str += 1;
	while (str[size] && str[size] != '"')
		size++;
	line = malloc(size + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '"')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**_split(char *str, char c)
{
	char	**argv;
	size_t	size;
	size_t	wordcount;
	size_t	i;

	i = 0;
	wordcount = wrdc(str);
	argv = malloc((wordcount + 1) * sizeof(char *));
	while (i < wordcount)
	{
		size = 0;
		while (*str && *str == c)
			str++;
		if (*str == '"')
		{
			argv[i] = _getline(str);
			str += ft_strlen(argv[i++]);
			continue;
		}
		while (str[size] && str[size] != c)
			size++;
		argv[i] = ft_strndup(str, size);
		str += size;
		i++;
	}
	return (argv[i] = NULL, argv);
}
