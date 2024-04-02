/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/31 03:01:42 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path()
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
		safe_exit(-1);
	return (curr_path);
}

int	cd(t_data *data)
{
	char	*curr_path;
	char	*old_path;

	old_path = get_curr_path();
	if (data->commands[1] == NULL)
	{
		if (chdir(env_grepvalue("HOME")) != 0)
			return (perror("Error\n"), 1);
		env_export("OLD_PWD", old_path);
		curr_path = get_curr_path();
		env_export("PWD", curr_path);
		free (curr_path);
		return (1);
	}
	if (chdir(data->commands[1]) != 0)
		return (printf("no such ile or directory: %s\n", data->commands[1]), 1);
	curr_path = get_curr_path();
	env_export("PWD", curr_path);
	env_export("OLD_PWD", old_path);
	free (curr_path);
	return (1);
}
