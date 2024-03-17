/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/16 17:52:29 by aabouqas         ###   ########.fr       */
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

int	wc(char *s)
{
	int wc;
	int d;

	wc = 0;
	d = 0;
	while (s && *s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s == '"')
			s = ft_strchr(s + 1, '"');
		else
			s = ft_strchr(s, ' ');
		if (s)
			wc++;
	}
	return (wc);
}

size_t	word_counter(char *rdline)
{
	size_t	wc;
	int		found_dqt;

	wc = 0;
	found_dqt = 0;
	while (rdline && *rdline)
	{
		while (*rdline != '\0' && *rdline == ' ')
			rdline++;
		wc += (*rdline != '\0');
		while (*rdline && (*rdline != ' ' || found_dqt == 1))
		{
			if (*rdline == '\"')
				found_dqt = (found_dqt == 0);
			rdline++;
		}
	}
	return (wc);
}

char	*get_line(char *str)
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

char	**_split(char *rdline, char c)
{
	char	**argv;
	size_t	size;
	size_t	wordcount;
	size_t	i;

	i = 0;
	wordcount = word_counter(rdline);
	argv = malloc((wordcount + 1) * sizeof(char *));
	while (i < wordcount)
	{
		while (*rdline && *rdline == c)
			rdline++;
		if (*rdline == '"')
		{
			argv[i] = get_line(rdline);
			rdline += ft_strlen(argv[i]) + 2;
		} else if (i < wordcount - 1){
			argv[i] = ft_strndup(rdline, ft_strchr(rdline, ' ') - rdline);
			rdline += ft_strlen(argv[i]);
		} else {
			argv[i] = ft_strndup(rdline, ft_strlen(rdline));
			rdline += ft_strlen(argv[i]);
		}
		i++;
	}
	return (argv[i] = NULL, argv);
}
