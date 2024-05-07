/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:07:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/07 15:36:25 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_valid_redrict(char *file_name)
{
	if (file_name && *file_name == '\0')
	{
		do_error(NSFODIR_ERR, file_name);
		return (0);
	}
	// char	*str;

	// str = _strdup(file_name);
	// str = expand_arg(str, 0);
	// if (str == NULL || *str == '\0')
	// {
	// 	do_error(NSFODIR_ERR, str);
	// 	free (str);
	// 	return (0);
	// }
	// free (str);
	return (1);
}

int	check_ambiguous(char *file_name)
{
	if (file_name == NULL)
	{
		do_error(AMBIGUOUS_ERR, file_name);
		return (0);
	}
	// char	*str;

	// if (_strchr(file_name, '$') == NULL)
	// 	return (1);
	// if (_strchr(file_name, SQT) != NULL || _strchr(file_name, DQT) != NULL)
	// 	return (1);
	// str = _strdup(file_name);
	// str = expand_arg(str, 0);
	// if (str == NULL || *str == '\0')
	// {
	// 	do_error(AMBIGUOUS_ERR, file_name);
	// 	free (str);
	// 	return (0);
	// }
	// free (str);
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
		if (check_valid_redrict(arg->next->value) == 0)
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
	if (usrin->type == ARG_PIPE)
		return (do_error(SYNTAX_ERR, usrin->value), 0);
	while (usrin)
	{
		if (check_syntax(usrin) == 0)
			return 0;
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
