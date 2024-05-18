/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:37 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/17 15:15:54 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	_free_child(void)
{
	t_data	*data;

	data = data_hook(NULL);
	_free_nodes(data->args);
	data->args = NULL;
	close(data->def_in);
	close(data->def_out);
	env_free_list(data->env);
	data->env = NULL;
	free(data->usrinput);
	data->usrinput = NULL;
	free(data->prompt);
	data->prompt = NULL;
	free (data->pwd);
	data->pwd = NULL;
}

void	child_proc_free(t_cmd *cmdptr, t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*cmds;

	cmds = data->cmds;
	_free_child();
	while (cmds)
	{
		tmp = cmds->next;
		if (cmds != cmdptr)
		{
			if (cmds->in != 0)
				close(cmds->in);
			if (cmds->out != 1)
				close(cmds->out);
			_free_nodes(cmds->linked_argv);
			cmds->linked_argv = NULL;
			free(cmds);
		}
		else
		{
			_free_nodes(cmds->linked_argv);
			cmds->linked_argv = NULL;
		}
		cmds = tmp;
	}
}

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
