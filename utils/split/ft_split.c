/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/30 18:50:21 by aabouqas         ###   ########.fr       */
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
	t_qutoes	qt;

	qt.dqt = 0;
	qt.sqt = 0;
	while (str && *str)
	{
		str = skiper(str);
		while (*str && (!is_white_spaces(*str) || qt.dqt || qt.sqt))
		{
			(*str == '\"' && !qt.sqt) && (qt.dqt = !qt.dqt);
			(*str == '\'' && !qt.dqt) && (qt.sqt = !qt.sqt);
			str++;
		}
		if (qt.dqt || qt.sqt)
			return (0);
	}
	return (1);
}

char	**_split(char *str)
{
	char		**argv;
	char		*res;
	t_qutoes	qt;

	(1) && (qt.dqt = 0, qt.sqt = 0, argv = NULL);
	while (*str)
	{
		(1) && (str = skiper(str) - 1, res = NULL);
		while (*(++str) && (!is_white_spaces(*str) || qt.dqt || qt.sqt))
		{
			(*str == '\"' && !qt.sqt) && (qt.dqt = (qt.dqt == 0));
			(*str == '\'' && !qt.dqt) && (qt.sqt = (qt.sqt == 0));
			if ((qt.dqt && *str != '"') || (qt.sqt && *str != '\'')
				|| (!qt.dqt && !qt.sqt && !ft_strchr("\'\"", *str)))
			{
				if (*str == '$' && qt.sqt == 0
					&& ft_isalnum(*(str +1) || ft_strchr("\'\"", *(str +1))))
					str += set_var(str + 1, &res);
				else if (ft_strchr("<>|", *str))
					argv = _realloc(argv, _strnjoin(NULL, str, 1));
				else
					res = _strnjoin(res, str, 1);
			}
		}
		argv = _realloc(argv, res);
	}
	return (argv);
}
