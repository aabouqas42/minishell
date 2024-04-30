/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:07:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/30 15:44:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_redirections(char **usrin)
{
	char	**args;
	int		i;

	i = 0;
	args = NULL;
	if (is_same(usrin[0], "|"))
		return (do_error(SYNTAX_ERR, usrin[0]), 0);
	while (usrin && usrin[i])
	{
		if (is_io_op(usrin[i]) && usrin[i + 1] == NULL)
				return (do_error(SYNTAX_ERR, "newline"), 0);
		if (_strchr("<>", usrin[i][0]) && !is_same(usrin[i], "<<"))
		{
			// if (usrin[i + 1] && usrin[i + 1][0] == '$')
			// 	if (!(_strchr(usrin[i +1], '\"') || _strchr(usrin[i + 1], '\'')))
			// 		if (!env_grepvalue(&usrin[i + 1][1]))
			// 			return (do_error(AMBIGUOUS_ERR, usrin[i + 1]), 0);
			if (_strchr("<>|", usrin[i + 1][0]))
				return (do_error(SYNTAX_ERR, usrin[i + 1]), 0);
		}
		if (_strchr("|", usrin[i][0]) && _strchr("|", usrin[i + 1][0]))
			return (do_error(SYNTAX_ERR, usrin[i + 1]), 0);
		i++;
	}
	return (1);
}
