/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:34:25 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/05 13:53:53 by aabouqas         ###   ########.fr       */
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

t_cmd	*get_commands(t_arg *argv)
{
	t_data	*data;
	t_arg	*args;
	t_cmd	*cmds;
	int		i;
	int		j;

	data = data_hook(NULL);
	args = data->_args;
	i = 0;
	j = 0;
	while (args)
	{
		while (args->type != ARG_PIPE)
		{
			args = args->next;
		}
		// while (data->args[i] && !(is_same(data->args[i], "|")))
		// {
		// 	cmds[j].argv = _realloc(cmds[j].argv, data->args[i]);
		// 	i++;
		// }
		// if (data->args[i] != NULL)
		// {
		// 	free (data->args[i]);
		// 	data->args[i] = NULL;
		// 	i++;
		// }
		j++;
	}
	return (cmds);
}
