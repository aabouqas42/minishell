/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/19 22:20:46 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void ft_switch_binary(int *b, int condition)
{
	if (condition)
	{
		if (*b == 0)
			*b = 1;
		else
			*b = 0;
	}
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

size_t	get_size(char *str)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;

	return (size);
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	size_t	size;
	size_t	j;
	char	*res;

	if (str == NULL)
		return (NULL);
	i = 0;
	size = 0;
	while (str[i] && i < n)
		size += (str[i] != '\\' && (!ft_strchr("\"\'", str[i])
			|| (str[i] == '"' && str[i - 1] == '\\'))), i++;
	// printf("%zu\n", size);
	res = malloc(size + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		if (str[i] != '\\' && (str[i] != '"'
			|| (str[i] == '"' && str[i - 1] == '\\')))
				res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	// printf("str : [%s] res [%s]\n", str, res);
	return (res);
}

char	**_split(char *str)
{
	int		found_dqt;
	char	**argv;
	size_t	size;
	size_t	wc;
	size_t	i;

	i = 0;
	found_dqt = 0;
	wc = argument_count(str);
	argv = malloc ((wc + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	while (i < wc)
	{
		size = 0;
		while (*str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || found_dqt == 1))
			ft_switch_binary(&found_dqt, (ft_strchr("\'\"", str[size]) && str[size - 1] != '\\')), size++;
		argv[i++] = ft_strndup(str, size);
		str += size;
		if (found_dqt)
			(printf("error \n"), exit(0));
	}
	return (argv[i] = NULL, argv);
}
