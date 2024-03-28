/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/28 18:09:13 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	args_is_valid(char *str)
{
	int		i;
	int		dqt;
	int		sqt;

	dqt = 0;
	sqt = 0;
	while (str && *str)
	{
		i = 0;
		while (*str && *str == ' ')
			str++;
		while (str[i] && (str[i] != ' ' || dqt || sqt))
		{
			(str[i] == '\"' && !sqt) && (dqt = !dqt);
			(str[i] == '\'' && !dqt) && (sqt = !sqt);
			i++;
		}
		if (dqt || sqt)
			return (0);
		str += i;
	}
	return (1);
}

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
	if (!args_is_valid(str))
		return (printf("Invalid Args..\n"), NULL);
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
		argv = _realloc(argv, _expander(str));
		str += size + 1;
		i++;
	}
	return (argv);
}
