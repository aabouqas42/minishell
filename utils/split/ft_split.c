/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/23 10:12:16 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skiper(char *str)
{
	while (str && *str && _spaces(*str))
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
		while (*str && (!_spaces(*str) || qt.dqt || qt.sqt))
		{
			if (*str == '\"' && !qt.sqt)
				(qt.dqt = !qt.dqt);
			if (*str == '\'' && !qt.dqt)
				(qt.sqt = !qt.sqt);
			str++;
		}
		if (qt.dqt || qt.sqt)
			return (0);
	}
	return (1);
}

size_t	set_arg(char *str, char **res, t_qutoes qt)
{
	size_t	size;
	char	c;
	char	nc;

	c = *str;
	nc = *(str + 1);
	size = 0;
	// if ((qt.dqt && c != '"') || (qt.sqt && c != '\'')
	// 	|| (!qt.dqt && !qt.sqt && !ft_strchr("\'\"", c)))
	// {
	if (c == '$' && qt.sqt == 0 && (ft_isalnum(nc) || ft_strchr("\'\"", nc)))
		size += set_var(str + 1, res) + 1;
	else
		(1) && (*res = _strnjoin(*res, str, 1), (size++));
	// }
	// if (size == 0)
	// 	return (1);
	return (size);
}

//
// char	**_split(char *str)
// {
// 	char		**commands;
// 	char		*res;
// 	t_qutoes	qt;
// 	ft_bzero(&qt, sizeof(t_qutoes));
// 	commands = NULL;
// 	data_hook(NULL)->commands = commands;
// 	while (*str)
// 	{
// 		(1) && (str = skiper(str), res = NULL);
// 		while (*str && !ft_strchr("<>|", *str) && ((!_spaces(*str) || qt.dqt || qt.sqt)))
// 		{
// 			(*str == '\"' && !qt.sqt) && (qt.dqt = (qt.dqt == 0));
// 			(*str == '\'' && !qt.dqt) && (qt.sqt = (qt.sqt == 0));
// 			str += set_arg(str, &res, qt);
// 		}
// 		commands = _realloc(commands, res);
// 		if (!ft_strncmp("<<", str, 2) || !ft_strncmp(">>", str, 2))
// 			(1) && (commands = _realloc(commands, _strnjoin(NULL, str, 2)), str += 2);
// 		else if (str && *str && ft_strchr("<>|", *str) != NULL)
// 			(1) && (commands =_realloc(commands, _strnjoin(NULL, str, 1)), str++);
// 	}
// 	return (commands);
// }

void	_split(char *str)
{
	char	***args_ptr;
	char	*res;
	char	qt;

	args_ptr = &data_hook(NULL)->args;
	while (*str)
	{
		(1) && (str = skiper(str), res = NULL, qt = 0);
		while (*str && (!_spaces(*str) || qt))
		{
			if ((*str == '\"' && qt != '\'') || (*str == '\'' && qt != '\"'))
				qt = (qt == 0) * (*str);
			if (ft_strchr("<>|", *str) && !qt)
				break;
			if (*str == '$' && qt != '\'' && (ft_isalnum(*(str +1)) || ft_strchr("\'\"", *(str +1))))
				str += set_var(str + 1, &res) + 1;
			else
				(1) && (res = _strnjoin(res, str, 1), str++);
		}
		*args_ptr = _realloc(*args_ptr, res);
		if (!ft_strncmp("<<", str, 2) || !ft_strncmp(">>", str, 2))
			(1) && (*args_ptr = _realloc(*args_ptr, _strnjoin(NULL, str, 2)), str +=2);
		else if (str && *str && ft_strchr("<>|", *str) != NULL)
			(1) && (*args_ptr = _realloc(*args_ptr, _strnjoin(NULL, str, 1)), str++);
	}
}
