/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:34:25 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/03 15:46:18 by aabouqas         ###   ########.fr       */
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
		if (cmds[i] && ft_strncmp(cmds[i], "|", 3) == 0)
			j++;
		i++;
	}
	return (j + 1);
}

char	***get_commands(void)
{
	char	***cmds;
	char	**args;
	int		i;
	int		j;

	args = data_hook(NULL)->args;
	cmds = _calloc((cmds_counter(args) + 1) * sizeof(char **));
	(1) && (i = 0, j = 0);
	while (args && args[i])
	{
		if (is_same(args[i], "|") && data_hook(NULL)->flags[i])
		{
			free (args[i]);
			args[i] = NULL;
			j++;
		}
		else
			cmds[j] = _realloc(cmds[j], args[i]);
		i++;
	}
	return (cmds);
}




