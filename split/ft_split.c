/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/10 11:59:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skiper(char *str)
{
	while (str && *str && _spaces(*str))
		str++;
	return (str);
}

int	_spaces(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
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
	return (*str != '\0');
}

void	mini_api(char *res)
{
	t_data	*data;
	int		heredoc_expand;

	data = data_hook(NULL);
	heredoc_expand = (_strchr(res, DQT) || _strchr(res, SQT));
	if (!_strchr(res, '$') || (get_last(data->args)
			&& get_last(data->args)->type == ARG_HERDOC))
		res = exp_with_no_qts(res, 1);
	else
	{
		res = exp_with_qts(res, 0);
		split_expanded(res);
		free (res);
		return ;
	}
	if (heredoc_expand)
		t_arg_add(res, ARG_QT);
	else
		t_arg_add(res, ARG_WORD);
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
		mini_api(res);
		usr_in += is_symbole(usr_in);
	}
}
