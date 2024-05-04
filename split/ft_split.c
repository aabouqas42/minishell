/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/04 15:19:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skiper(char *str)
{
	while (str && *str && _spaces(*str))
		str++;
	return (str);
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

void	split_usrin(char *usr_in)
{
	char	***args_ptr;
	char	*res;
	char	qt;

	args_ptr = &data_hook(NULL)->args;
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
		*args_ptr = _realloc(*args_ptr, res);
		usr_in += is_symbole(args_ptr, usr_in);
	}
}
