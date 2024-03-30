/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/30 04:00:26 by aabouqas         ###   ########.fr       */
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
	char		**argv;
	char		*res;
	t_qutoes	q;

	(1) && (q._double = 0, q._single = 0, argv = NULL);
	while (*str)
	{
		(1) && (str = skiper(str) - 1, res = NULL);
		while (*(++str) && (!is_white_spaces(*str) || q._double || q._single))
		{
			(*str == '\"' && !q._single) && (q._double = (q._double == 0));
			(*str == '\'' && !q._double) && (q._single = (q._single == 0));
			if ((q._double && *str != '"') || (q._single && *str != '\'')
				|| (!q._double && !q._single && !ft_strchr("\'\"", *str)))
			{
				if (*str == '$' && q._single == 0
					&& ft_isalnum(*(str +1) || ft_strchr("\'\"", *(str +1))))
					str += set_var(str + 1, &res);
				else
					res = _strnjoin(res, str, 1);
			}
		}
		argv = _realloc(argv, res);
	}
	return (argv);
}
