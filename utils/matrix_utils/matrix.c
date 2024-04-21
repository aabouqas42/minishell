/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:34:25 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/21 17:13:51 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmds_counter(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds && cmds[i])
	{
		if (is_same(cmds[i], "|") == 0)
			j++;
		i++;
	}
	return (j + 1);
}

char	***get_commands()
{
	char	***cmds;
	char	**commands;
	int		i;

	commands = data_hook(NULL)->commands;
	if (check_input() == -1)
	{
		do_error(SYNTAX_ERR);
		return (NULL);
	}
	cmds = _calloc((cmds_counter(commands) + 1) * sizeof(char **));
	i = 0;
	while (commands && *commands)
	{
		if (is_same(*commands, "|") == 0)
			cmds[i] = _realloc(cmds[i], *commands);
		else
			i++;
		commands++;
	}
	return (cmds);
}

void	free_matrix(char ***matrix)
{
	int	i;

	if (matrix == NULL)
		return ;
	i = 0;
	while (matrix[i])
	{
		free_tab(matrix[i]);
		i++;
	}
	free (matrix);
}