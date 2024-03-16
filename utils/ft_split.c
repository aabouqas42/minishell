/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/16 02:48:26 by aabouqas         ###   ########.fr       */
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
		printf("[%s]\n", rdline);
		while (*rdline && (*rdline != ' ' || found_dqt == 1))
		{
			if (*rdline == '\"')
				found_dqt = (found_dqt == 0);
			rdline++;
		}
	}
	return (wc);
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
		size = (size_t)rdline;
		while (*rdline && *rdline == c)
			rdline++;
		size -= (size_t) rdline;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
