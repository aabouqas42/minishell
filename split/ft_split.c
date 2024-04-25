/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/25 13:24:06 by aabouqas         ###   ########.fr       */
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
		if (qt == '\'')
			return (do_error(SYNTAX_ERR, "\'"), 0);
		if (qt == '\"')
			return (do_error(SYNTAX_ERR, "\""), 0);
		str+= (*str != '\0');
	}
	return (1);
}

size_t	is_symbole(char ***args_ptr, char *str)
{
	if (!ft_strncmp("<<", str, 2) || !ft_strncmp(">>", str, 2))
	{
		*args_ptr = _realloc(*args_ptr, _strnjoin(NULL, str, 2));
		return (2);
	}
	if (str && *str && ft_strchr("<>|", *str) != NULL)
		*args_ptr = _realloc(*args_ptr, _strnjoin(NULL, str, 1));
	return (1);
}

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
			if (*str == '$' && (qt == 0 && *(str + 1) && ft_strchr("\'\"", *(str + 1))))
			{
				str++;
				continue;
			} else if (*str == '$' && qt != '\'' && (ft_isalnum(*(str + 1)) || (*(str + 1) && ft_strchr("_?", *(str + 1)))))
				str += set_var(str + 1, &res) + 1;
			else
				(1) && (res = _strnjoin(res, str, 1), str++);
		}
		*args_ptr = _realloc(*args_ptr, res);
		str += is_symbole(args_ptr, str);
	}
}
