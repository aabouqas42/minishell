/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/08 09:56:00 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_case(char curr_char, char next_char)
{
	return (curr_char == '$' && _strchr("\'\"", next_char));
}

int	var_case(char curr_char, char next_char)
{
	if (curr_char == '$')
		if (ft_isalnum(next_char) || (next_char && _strchr("_?", next_char)))
			return (1);
	return (0);
}

char	*expand_arg(char *str, int hd)
{
	char	*ptr;
	char	*res;
	char	qt;

	(1337) && (qt = 0, res = NULL, ptr = str);
	while (str && *str != '\0')
	{
		if ((*str == DQT && qt != SQT) || (*str == SQT && qt != DQT))
		{
			qt = (qt == 0) * (*str);
			if (qt == 0)
				res = _strnjoin(res, "", 1);
		}
		else if (skip_case(*str, *(str + 1)) && qt == 0)
		{
			str++;
			continue ;
		}
		else if (qt != SQT && var_case(*str, *(str + 1)) && !hd)
			str += set_var((str + 1), &res);
		else
			res = _strnjoin(res, str, 1);
		str++;
	}
	return (free (ptr), res);
}

void	expand_input(t_arg *args)
{
	char	*expanded;

	while (args)
	{
		if (args->type == ARG_HERDOC)
		{
			expanded = expand_arg(args->next->value, 1);
			args = args->next;
		}
		else
		{
			expanded = expand_arg(args->value, 0);
		}
		args->value = expanded;
		args = args->next;
	}
	// printf("--------\n");
	// prt_list(data_hook(NULL)->args);
	// printf("--------\n");
}
