/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/24 12:29:12 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skiper(char *str)
{
	while (str && *str && _spaces(*str))
		str++;
	return (str);
}

int	check_quotes_closed(char *str)
{
	char	qt;

	qt = 0;
	while (str && *str)
	{
		str = skiper(str);
		while (*str && (!_spaces(*str) || qt))
		{
			if ((*str == '\"' && qt != '\'') || (*str == '\'' && qt != '\"'))
				qt = (qt == 0) * (*str);
			str++;
		}
		if (qt)
		{
			if (qt == '\'')
				return (do_error(SYNTAX_ERR, "\'"), 0);
			if (qt == '\"')
				return (do_error(SYNTAX_ERR, "\""), 0);
		}
		if (*str)
			str++;
	}
	return (1);
}

// size_t	set_arg(char *str, char **res, t_qutoes qt)
// {
// 	size_t	size;
// 	char	c;
// 	char	nc;

// 	c = *str;
// 	nc = *(str + 1);
// 	size = 0;
// 	// if ((qt.dqt && c != '"') || (qt.sqt && c != '\'')
// 	// 	|| (!qt.dqt && !qt.sqt && !ft_strchr("\'\"", c)))
// 	// {
// 	if (c == '$' && qt.sqt == 0 && (ft_isalnum(nc) || ft_strchr("\'\"", nc)))
// 		size += set_var(str + 1, res) + 1;
// 	else
// 		(1) && (*res = _strnjoin(*res, str, 1), (size++));
// 	// }
// 	// if (size == 0)
// 	// 	return (1);
// 	return (size);
// }


// void	_split(char *str)
// {
// 	char		***args;
// 	char		*res;
// 	t_qutoes	qt;

// 	ft_bzero(&qt, sizeof(t_qutoes));
// 	args = &data_hook(NULL)->args;
// 	while (*str)
// 	{
// 		(1) && (str = skiper(str), res = NULL);
// 		while (*str && ((!_spaces(*str) || qt.dqt || qt.sqt)))
// 		{
// 			(*str == '\"' && !qt.sqt) && (qt.dqt = (qt.dqt == 0));
// 			(*str == '\'' && !qt.dqt) && (qt.sqt = (qt.sqt == 0));
// 			if (ft_strchr("<>|", *str && !qt.dqt && !qt.sqt))
// 				break ;
// 			str += set_arg(str, &res, qt);
// 		}
// 		*args = _realloc(*args, res);
// 		if (!ft_strncmp("<<", str, 2) || !ft_strncmp(">>", str, 2))
// 			(1) && (*args = _realloc(*args, _strnjoin(NULL, str, 2)), str += 2);
// 		else if (str && *str && ft_strchr("<>|", *str) != NULL)
// 			(1) && (*args =_realloc(*args, _strnjoin(NULL, str, 1)), str++);
// 	}
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
			if (*str == '$' && qt != '\'' && (ft_isalnum(*(str + 1)) || (ft_strchr("\'\"", *(str + 1)) && *(str + 2))))
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
