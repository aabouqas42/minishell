/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:37 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/06 19:13:42 by aabouqas         ###   ########.fr       */
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

void	free_matrix(char ***matrix)
{
	int	i;

	if (matrix == NULL)
		return ;
	i = 0;
	while (matrix[i] != NULL)
	{
		free_tab(matrix[i]);
		i++;
	}
	free (matrix);
}

void	_free(void)
{
	t_data	*data;

	data = data_hook(NULL);
	t_arg_free(data->args);
	data->args = NULL;
	// free_tab(data->heredocs);
	data->heredocs = NULL;
	t_cmd_free(data->cmds);
	data->cmds = NULL;
	free (data->args);
	data->args = NULL;
	free (data->usrinput);
	data->usrinput = NULL;
}
