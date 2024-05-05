/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 19:51:42 by mait-elk         ###   ########.fr       */
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

void	expand_arg(char *str, char ***args, int after_hd)
{
	char	*res;
	char	qt;

	qt = 0;
	res = NULL;
	while (str && *str != '\0')
	{
		if ((*str == '\"' && qt != '\'') || (*str == '\'' && qt != '\"'))
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
		else if (qt != '\'' && var_case(*str, *(str + 1)) && !after_hd)
			str += set_var((str + 1), &res);
		else
			res = _strnjoin(res, str, 1);
		str++;
	}
	(1) && (res != NULL && (*args = _realloc(*args, res)));
}

void	expand_input(char **uin)
{
	char	**args;
	int		i;

	args = NULL;
	i = 0;
	while (uin && uin[i] != NULL)
	{
		expand_arg(uin[i], &args, (i != 0 && is_same(uin[i -1], "<<")
				&& data_hook(NULL)->flags[i -1].is_io_op));
		i++;
	}
	free_tab(data_hook(NULL)->args);
	data_hook(NULL)->args = args;
}
