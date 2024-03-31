/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/30 17:56:25 by mait-elk         ###   ########.fr       */
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

	if (data->argv[1] == NULL)
	{
		chdir(env_grepvalue("HOME"));
		curr_path = get_curr_path();
		env_export("PWD", curr_path);
		free (curr_path);
		return (1);
	}
	if (chdir(data->argv[1]) != 0)
		return (printf("no such ile or directory: %s\n", data->argv[1]), 1);
	curr_path = get_curr_path();
	env_export("PWD", curr_path);
	free (curr_path);
	return (1);
}
