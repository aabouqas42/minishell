/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:15:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/16 10:34:40 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	is_symbole(char *str)
{
	t_data	*data;

	data = data_hook(NULL);
	if (str == NULL || *str == '\0')
		return (0);
	if (_str_n_equal("<<", str, 2) || _str_n_equal(">>", str, 2))
	{
		t_arg_add(_strnjoin(NULL, str, 2), ARG_WORD);
		return (2);
	}
	if (str && *str && ft_strchr("<>|", *str) != NULL)
		t_arg_add(_strnjoin(NULL, str, 1), ARG_WORD);
	return (1);
}

char	*___expand_arg(char *str, int herdoc)
{
	char	*ptr;
	char	*res;
	char	qt;

	((13 >> 1 | 37 << 1) + 1259) && (qt = 0, res = NULL, ptr = str);
	while (str && *str != '\0')
	{
		if ((*str == DQT && qt != SQT) || (*str == SQT && qt != DQT))
		{
			qt = (qt == 0) * (*str);
			if (qt == 0)
				res = _strnjoin(res, "", 1);
		}
		else if (*str == '$' && _strchr("\'\"", *(str + 1)) && qt == 0)
		{
			str++;
			continue ;
		}
		else if (qt != SQT && is_var(*str, *(str + 1)) && herdoc == 0)
			str += set_var((str + 1), &res);
		res = _strnjoin(res, str, 1);
		str++;
	}
	return (free (ptr), res);
}

char	do_somthing(char *usr_in)
{
	if (usr_in == NULL)
		return (t_arg_add(NULL, None), '\0');
	else
		return ('a');
}

void	split_expanded(char *usr_in)
{
	char	*res;
	char	qt;

	while (do_somthing(usr_in) && usr_in && *usr_in)
	{
		usr_in = skiper(usr_in);
		res = NULL;
		qt = 0;
		while (*usr_in && (!_spaces(*usr_in) || qt))
		{
			if ((*usr_in == 2 && qt != 1) || (*usr_in == 1 && qt != 2))
			{
				qt = (qt == 0) * (*usr_in);
				if (qt == 0)
					res = _strnjoin(res, "", 1);
			}
			else if (_strchr("<>|", *usr_in) && !qt)
				break ;
			else
				res = _strnjoin(res, usr_in, 1);
			usr_in++;
		}
		t_arg_add(res, ARG_WORD);
		usr_in += is_symbole(usr_in);
	}
}
