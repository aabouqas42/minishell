/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/21 17:51:19 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path(t_data *data)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
	{
		_free(data);
		exit(-1);
	}
	return (curr_path);
}

int	cd(t_data *data)
{
	char	*curr_path;

	if (data->argv[1] == NULL)
	{
		chdir(env_grep_value("HOME", data));
		curr_path = get_curr_path(data);
		env_export("PWD", curr_path, data);
		free (curr_path);
		return (1);
	}
	if (chdir(data->argv[1]) != 0)
		return (printf("no such ile or directory: %s\n", data->argv[1]), 1);
	curr_path = get_curr_path(data);
	env_export("PWD", curr_path, data);
	free (curr_path);
	return (1);
}
