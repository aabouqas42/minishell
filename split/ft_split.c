/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/06 17:34:25 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skiper(char *str)
{
	while (str && *str && _spaces(*str))
		str++;
	return (str);
}

size_t	is_symbole(char *str)
{
	if (!ft_strncmp("<<", str, 2))
	{
		t_arg_add(_strnjoin(NULL, str, 2), ARG_HERDOC);
		return (2);
	}
	if (!ft_strncmp(">>", str, 2))
	{
		t_arg_add(_strnjoin(NULL, str, 2), ARG_APPEND);
		return (2);
	}
	if (str && *str && ft_strchr("<>|", *str) != NULL)
	{
		if (ft_strncmp("|", str, 1) == 0)
			t_arg_add(_strnjoin(NULL, str, 1), ARG_PIPE);
		if (ft_strncmp("<", str, 1) == 0)
			t_arg_add(_strnjoin(NULL, str, 1), ARG_REDIN);
		if (ft_strncmp(">", str, 1) == 0)
			t_arg_add(_strnjoin(NULL, str, 1), ARG_REDOUT);
	}
	return (1);
}

void	split_usrin(char *usr_in)
{
	char	*res;
	char	qt;

	while (*usr_in)
	{
		usr_in = skiper(usr_in);
		res = NULL;
		qt = 0;
		while (*usr_in && (!_spaces(*usr_in) || qt))
		{
			if ((*usr_in == DQT && qt != SQT) || (*usr_in == SQT && qt != DQT))
				qt = (qt == 0) * (*usr_in);
			if (ft_strchr("<>|", *usr_in) && !qt)
				break ;
			res = _strnjoin(res, usr_in, 1);
			usr_in++;
		}
		if (_strchr(res, DQT) || _strchr(res, SQT))
			t_arg_add(res, ARG_QT);
		else
			t_arg_add(res, ARG_WORD);
		usr_in += is_symbole(usr_in);
	}
}
