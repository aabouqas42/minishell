/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:37 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/09 15:20:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	_free(void)
{
	t_data	*data;
	t_arg	*t;
	t_cmd	*tmp;

	data = data_hook(NULL);
	t_arg_free(data->args);
	data->args = NULL;
	while (data->cmds)
	{
		tmp = data->cmds->next;
		free(data->cmds->argv);
		while (data->cmds->linked_argv)
		{
			t = data->cmds->linked_argv->next;
			free(data->cmds->linked_argv);
			data->cmds->linked_argv = t;
		}
		free(data->cmds);
		data->cmds = tmp;
	}
	1 && (free(data->program_path), data->program_path = NULL);
	1 && (free_tab(data->env_2d), data->env_2d = NULL);
	1 && (free(data->usrinput), data->usrinput = NULL);
}
