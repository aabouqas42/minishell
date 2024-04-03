/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:26:50 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/02 17:55:53 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


int	_pipe(char **commands)
{
	int	i;
	int	child;
	int	fds[2];
	t_data	*data;

	i = 0;
	data = data_hook(NULL);
	while (commands[i])
	{
		if (*commands[i] == '|')
		{
			commands[i] = NULL;
			if (is_valid_cmd(data, commands[0]) != 1)
				return (perror("Err\n"), 1);
			dup2(fds[1], 1);
			dup2(fds[0], 0);
			child = fork();
			if (child == 0)
				execve(data->program_path, commands, NULL);
			i++;
		}
		i++;
	}
	return (0);
}
