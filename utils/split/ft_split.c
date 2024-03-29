/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/29 01:36:28 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_white_spaces(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*skiper(char *str)
{
	while (str && *str && is_white_spaces(*str))
		str++;
	return (str);
}

size_t	args_is_valid(char *str)
{
	int		dqt;
	int		sqt;

	dqt = 0;
	sqt = 0;
	while (str && *str)
	{
		str = skiper(str);
		while (*str && (!is_white_spaces(*str) || dqt || sqt))
		{
			(*str == '\"' && !sqt) && (dqt = !dqt);
			(*str == '\'' && !dqt) && (sqt = !sqt);
			str++;
		}
		if (dqt || sqt)
			return (0);
	}
	return (1);
}

char	**_split(char *str)
{
	char	**argv;
	size_t	size;
	int		dqt;
	int		sqt;

	dqt = 0;
	sqt = 0;
	argv = NULL;
	if (!args_is_valid(str))
		return (printf("Invalid Args..\n"), NULL);
	while (*str)
	{
		size = 0;
		str = skiper(str);
		while (str[size] && (!is_white_spaces(str[size]) || dqt || sqt))
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
	}
	return (argv);
}
