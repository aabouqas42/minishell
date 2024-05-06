/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:37 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/06 20:36:32 by aabouqas         ###   ########.fr       */
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

	data = data_hook(NULL);
	printf("[%p - %p]\n", data->args, data->cmds);
	t_cmd_free(data->cmds);
	free(data->args);
	data->cmds = NULL;
	// t_arg_free(data->args);
	data->args = NULL;
	printf("%p\n", data->heredocs);
	// free_tab(data->heredocs);
	// data->heredocs = NULL;
	free (data->usrinput);
	data->usrinput = NULL;
}
