/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:07:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/08 11:57:24 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_valid_redirect(char *file_name)
{
	if (file_name && *file_name == '\0')
	{
		do_error(NSFODIR_ERR, file_name);
		return (0);
	}
	return (1);
}

int	check_ambiguous(char *file_name)
{
	if (file_name == NULL)
	{
		do_error(AMBIGUOUS_ERR, file_name);
		return (0);
	}
	return (1);
}

int	check_syntax(t_arg *arg)
{
	if (arg->type > 1 && arg->next == NULL)
			return (do_error(SYNTAX_ERR, "newline"), 0);
	if ((arg->type >= 3 && arg->type <= 5))
	{
		if (check_ambiguous(arg->next->value) == 0)
			return (0);
		if (check_valid_redirect(arg->next->value) == 0)
			return (0);
		if (arg->next->type > 1)
			return (do_error(SYNTAX_ERR, arg->next->value), 0);
	}
	if (arg->type == ARG_HERDOC && arg->next->type > 1)
			return (do_error(SYNTAX_ERR, arg->next->value), 0);
	if (arg->type == ARG_PIPE && arg->next->type == ARG_PIPE)
		return (do_error(SYNTAX_ERR, arg->next->value), 0);
	return (1);
}

int	check_redirections(t_arg *usrin)
{
	if (usrin && usrin->type == ARG_PIPE)
		return (do_error(SYNTAX_ERR, usrin->value), 0);
	while (usrin)
	{
		if (check_syntax(usrin) == 0)
			return 0;
		usrin = usrin->next;
	}
	return (1);
}
