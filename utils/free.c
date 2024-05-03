/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:37 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/03 15:47:12 by aabouqas         ###   ########.fr       */
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
	free_matrix(data->cmds);
	data->cmds = NULL;
	free (data->args);
	data->args = NULL;
	free (data->flags);
	data->flags = NULL;
	free (data->usrinput);
	data->usrinput = NULL;
}