/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/28 02:07:07 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
