/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:50:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/07 10:11:14 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_qts(char *str)
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
		str += (*str != '\0');
	}
	return (1);
}
