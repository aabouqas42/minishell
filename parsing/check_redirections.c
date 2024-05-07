/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:07:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/07 10:29:39 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_heredoc(t_arg **userin)
{
	t_data	*data;

	data = data_hook(NULL);
	if ((*userin)->next && check_qts((*userin)->next->value))
	{
		if ((*userin)->type == ARG_HERDOC && (*userin)->next && (*userin)->next->type <= 1)
		{
			(*userin)->next->value = expand_arg((*userin)->next->value, 1);
			data->heredocs = _realloc(data->heredocs, (*userin)->next->value);
			(*userin) = (*userin)->next;
			return (1);
		}
		(*userin) = (*userin)->next;
	}
	return (0);
}

int	check_redirections(t_arg *usrin)
{
	if (usrin->type == ARG_PIPE)
		return (do_error(SYNTAX_ERR, usrin->value), 0);
	while (usrin)
	{
		if (usrin->type == ARG_QT && check_qts(usrin->value) == 0)
			return (0);
		if (usrin->type > 1 && usrin->next == NULL)
			return (do_error(SYNTAX_ERR, "newline"), 0);
		if (usrin->type == ARG_HERDOC && usrin->next->type > 1)
			return (do_error(SYNTAX_ERR, usrin->next->value), 0);
		if ((usrin->type == ARG_REDIN || usrin->type == ARG_REDOUT))
		{
			if (usrin->next && *(usrin->next->value) == '$')
				if (!(_strchr(usrin->next->value, DQT) || _strchr(usrin->next->value, SQT)))
					if (!env_grepvalue(usrin->next->value + 1))
						return (do_error(AMBIGUOUS_ERR, usrin->next->value), 0);
			if (_strchr("<>|", usrin->next->value[0]))
				return (do_error(SYNTAX_ERR, usrin->next->value), 0);
		}
		if (usrin->type == ARG_PIPE && usrin->next->type == ARG_PIPE)
			return (do_error(SYNTAX_ERR, usrin->next->value), 0);
		check_heredoc(&usrin);
		usrin = usrin->next;
	}
	return (1);
}

// int	check_redirections(t_arg *head)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = NULL;
// 	if (head == NULL)
// 		return 0;
// 	if (head && head->next)
// 		printf("[%s] [%s]\n", head->value, head->next->value);
// 	// if (usrin->type == ARG_PIPE)
// 	// 	return (do_error(SYNTAX_ERR, usrin->value), 0);
// 	if (head->type > 1 && head->next == NULL)
// 		return (do_error(SYNTAX_ERR, "newline"), 0);
// 	if ((head->type == ARG_REDIN || head->type == ARG_REDOUT))
// 	{
// 		if (head->next && *(head->next->value) == '$')
// 			if (!(_strchr(head->next->value, DQT) || _strchr(head->next->value, SQT)))
// 				if (!env_grepvalue(head->next->value + 1))
// 					return (do_error(AMBIGUOUS_ERR, head->next->value), 0);
// 		if (_strchr("<>|", head->next->value[0]))
// 			return (do_error(SYNTAX_ERR, head->next->value), 0);
// 	}
// 	if (head->type == ARG_PIPE && head->next->type == ARG_PIPE)
// 		return (do_error(SYNTAX_ERR, head->next->value), 0);
	// while (usrin)
	// {
	// 	// #error FIX THIS
	// 	// printf("%d\n", usrin->type > 1 && usrin->next == NULL);
	// 	if (usrin->type > 1 && usrin->next == NULL)
	// 		return (do_error(SYNTAX_ERR, "newline"), 0);
	// 	if ((usrin->type == ARG_REDIN || usrin->type == ARG_REDOUT))
	// 	{
	// 		if (usrin->next && *(usrin->next->value) == '$')
	// 			if (!(_strchr(usrin->next->value, DQT) || _strchr(usrin->next->value, SQT)))
	// 				if (!env_grepvalue(usrin->next->value + 1))
	// 					return (do_error(AMBIGUOUS_ERR, usrin->next->value), 0);
	// 		if (_strchr("<>|", usrin->next->value[0]))
	// 			return (do_error(SYNTAX_ERR, usrin->next->value), 0);
	// 	}
	// 	if (usrin->type == ARG_PIPE && usrin->next->type == ARG_PIPE)
	// 		return (do_error(SYNTAX_ERR, usrin->next->value), 0);
	// 	usrin = usrin->next;
	// }
// 	return (1);
// }

// int	check_redirections(char **usrin)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = NULL;
// 	if (is_same(usrin[0], "|"))
// 		return (do_error(SYNTAX_ERR, usrin[0]), 0);
// 	while (usrin && usrin[i])
// 	{
// 		if (is_io_op(usrin[i]) && usrin[i + 1] == NULL)
// 			return (do_error(SYNTAX_ERR, "newline"), 0);
// 		if (_strchr("<>", usrin[i][0]) && !is_same(usrin[i], "<<"))
// 		{
// 			if (usrin[i + 1] && usrin[i + 1][0] == '$')
// 				if (!(_strchr(usrin[i + 1], 34) || _strchr(usrin[i + 1], 39)))
// 					if (!env_grepvalue(&usrin[i + 1][1]))
// 						return (do_error(AMBIGUOUS_ERR, usrin[i + 1]), 0);
// 			if (_strchr("<>|", usrin[i + 1][0]))
// 				return (do_error(SYNTAX_ERR, usrin[i + 1]), 0);
// 		}
// 		if (_strchr("|", usrin[i][0]) && _strchr("|", usrin[i + 1][0]))
// 			return (do_error(SYNTAX_ERR, usrin[i + 1]), 0);
// 		i++;
// 	}
// 	return (1);
// }
