/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:15:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/09 10:31:29 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	is_symbole(char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	if (!ft_strncmp("<<", str, 2) || !ft_strncmp(">>", str, 2))
	{
		t_arg_add(_strnjoin(NULL, str, 2), ARG_WORD);
		return (2);
	}
	if (str && *str && ft_strchr("<>|", *str) != NULL)
		t_arg_add(_strnjoin(NULL, str, 1), ARG_WORD);
	return (1);
}

void	split_expanded(char *usr_in)
{
	char	*res;
	char	qt;

	if (usr_in == NULL)
		return ;
	while (*usr_in)
	{
		usr_in = skiper(usr_in);
		res = NULL;
		qt = 0;
		while (*usr_in && (!_spaces(*usr_in) || qt))
		{
			if ((*usr_in == DQT && qt != SQT) || (*usr_in == SQT && qt != DQT))
				qt = (qt == 0) * (*usr_in);
			if (_strchr("<>|", *usr_in) && !qt)
				break ;
			res = _strnjoin(res, usr_in, 1);
			usr_in++;
		}
		t_arg_add(res, ARG_WORD);
		usr_in += is_symbole(usr_in);
	}
}
