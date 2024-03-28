/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/28 02:05:15 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	**realloc_2d(char **origin, char *to_append)
// {
// 	size_t	size;
// 	size_t	i;
// 	char	**res;

// 	if (origin == NULL)
// 	{
// 		res = malloc(sizeof(char *) * 2);
// 		res[0] = to_append;
// 		res[1] = NULL;
// 		return (res);
// 	}
// 	size = 0;
// 	i = 0;
// 	while (origin && origin[size])
// 		size++;
// 	size++;
// 	res = malloc(sizeof(char *) * (size + 1));
// 	while (origin[i])
// 	{
// 		res[i] = origin[i];
// 		i++;
// 	}
// 	res[i++] =  to_append;
// 	res[i] = NULL;
// 	free(origin);
// 	return (res);
// }

char	**_split(char *str)
{
	char	**argv;
	size_t	size;
	size_t	i;
	int		dqt;
	int		sqt;
	// size_t	wc;

	i = 0;
	dqt = 0;
	sqt = 0;
	// wc = argument_count(str);
	// if (wc == 0)
	// 	return (printf("Invalid Args..\n"), NULL);
	// argv = p_calloc (sizeof(char *) * (wc + 1));
	argv = NULL;
	while (*str)
	{
		size = 0;
		while (*str && *str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || dqt || sqt))
		{
			if (str[size] == '\"' && !sqt)
				(dqt = (dqt == 0)), str[size] = 2;
			if (str[size] == '\'' && !dqt)
				(sqt = (sqt == 0)), str[size] = 1;
			size++;
		}
		str[size] = '\0';
		argv = realloc_2d(argv, _strndup(str));
		str += size + 1;
		i++;
	}
	return (argv);
}
