/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/02 17:09:53 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path(void)
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
	if (data->args[1] == NULL || is_io_op(data->args[1]))
	{
		if (chdir(env_grepvalue("HOME")) != 0)
			return (perror("Error\n"), 1);
		env_export("OLD_PWD", old_path);
		curr_path = get_curr_path();
		env_export("PWD", curr_path);
		free (curr_path);
		free (old_path);
		return (1);
	}
	if (is_fod(data->args[1]) == _FILE)
		return (printf("minishell cd: %s: Not a directory\n", data->args[1]), 1);
	if (chdir(data->args[1]) != 0)
		return (printf("no such file or directory: %s\n", data->args[1]), 1);
	curr_path = get_curr_path();
	env_export("PWD", curr_path);
	env_export("OLD_PWD", old_path);
	free (curr_path);
	free (old_path);
	return (1);
}
