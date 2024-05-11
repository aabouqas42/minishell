/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:37 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 10:43:48 by mait-elk         ###   ########.fr       */
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

void	_free_nodes(t_arg *nodes)
{
	t_arg	*next_node;

	while (nodes)
	{
		next_node = nodes->next;
		free (nodes);
		nodes = next_node;
	}
}

void	_free(void)
{
	t_data	*data;
	t_cmd	*next_argv;

	data = data_hook(NULL);
	t_arg_free(data->args);
	data->args = NULL;
	while (data->cmds)
	{
		next_argv = data->cmds->next;
		free(data->cmds->argv);
		_free_nodes(data->cmds->linked_argv);
		free(data->cmds);
		data->cmds = next_argv;
	}
	free(data->program_path);
	data->program_path = NULL;
	free_tab(data->env_2d);
	data->env_2d = NULL;
	free(data->usrinput);
	data->usrinput = NULL;
}
