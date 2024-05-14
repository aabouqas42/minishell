/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/12 14:51:11 by mait-elk         ###   ########.fr       */
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

int	mini_api(char *res)
{
	t_data	*data;
	t_arg	*lastarg;
	char	*save;
	int		heredoc_expand;

	data = data_hook(NULL);
	heredoc_expand = (_strchr(res, DQT) || _strchr(res, SQT));
	if (!_strchr(res, '$') || (t_arg_get_last(data->args)
			&& t_arg_get_last(data->args)->type == ARG_HERDOC))
		res = exp_with_no_qts(res, 1);
	else
	{
		lastarg = t_arg_get_last(data->args);
		save = _strdup(res);
		res = exp_with_qts(res, 0);
		split_expanded(res);
		if (lastarg && lastarg->type >= 2 && lastarg->type <= 5
			&& (res == NULL || t_arg_size(lastarg->next) > 1))
			return (do_error(AMBIGUOUS_ERR, "", save), free(save), 0);
		return (free(save), free(res), 1);
	}
	if (heredoc_expand)
		return (t_arg_add(res, ARG_QT), 1);
	t_arg_add(res, ARG_WORD);
	return (1);
}

int	split_usrin(char *usr_in)
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
		if (mini_api(res) == 0)
			return (0);
		usr_in += is_symbole(usr_in);
	}
	return (1);
}
