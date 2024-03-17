/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/17 18:02:54 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void ft_switch_binary(int *b, int condition)
{
	if (condition)
		*b = (*b == 0);
}

size_t	argument_count(char *rdline)
{
	size_t	wc;
	int		found_dqt;

	wc = 0;
	found_dqt = 0;
	while (rdline && *rdline)
	{
		while (*rdline == ' ')
			rdline++;
		wc += (*rdline != '\0');
		while (*rdline && (*rdline != ' ' || found_dqt))
		{
			ft_switch_binary(&found_dqt, (*rdline == '\"'));
			rdline++;
		}
	}
	return (wc);
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*res;

	if (str == NULL)
		return (NULL);
	res = malloc(n + 1);
	if (res == NULL)
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**_split(char *str)
{
	int		found_dqt;
	char	**argv;
	size_t	wc;
	size_t	i;
	size_t	size;

	i = 0;
	wc = argument_count(str);
	argv = malloc ((wc + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	found_dqt = 0;
	while (i < wc)
	{
		size = 0;
		while (*str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || found_dqt))
		{
			ft_switch_binary(&found_dqt, (str[size] == '\"'));
			size++;
		}
		argv[i] = ft_strndup(str, size);	
		str += size;
		// if (found_dqt)
		// 	(printf("error \n"), exit(0));
		i++;
	}
	return (argv[i] = NULL, argv);
}
