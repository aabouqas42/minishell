/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:50:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/10 19:04:54 by aabouqas         ###   ########.fr       */
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
		if (qt == SQT || qt == DQT)
		{
			if (qt == '\'')
				do_error(SYNTAX_ERR, "", "\'");
			if (qt == '\"')
				do_error(SYNTAX_ERR, "", "\"");
			return (0);
		}
		str += (*str != '\0');
	}
	return (1);
}
