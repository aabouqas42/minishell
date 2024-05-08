/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/08 11:11:44 by mait-elk         ###   ########.fr       */
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

t_arg	*get_last(t_arg *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	mini_api(char *res, int expand)
{
	t_data	*data;

	data = data_hook(NULL);
	if (expand)
	{
		if (get_last(data->args) && get_last(data->args)->type == ARG_HERDOC)
			res = expand_arg(res, 1);
		else
		{
			res = expand_arg(res, 0);
			split_usrin(res, 0);
			return ;
		}
	}
	if (_strchr(res, DQT) || _strchr(res, SQT))
		t_arg_add(res, ARG_QT);
	else
		t_arg_add(res, ARG_WORD);
}

void	split_usrin(char *usr_in, int expand)
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
		mini_api(res, expand);
		usr_in += is_symbole(usr_in);
	}
}
