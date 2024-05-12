/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/12 11:00:31 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path(int p)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
	{
		if (p)
			custom_err("pwd", "getcwd", "Unexpected Error", 255);
		return (NULL);
	}
	return (curr_path);
}

int	go_to_home(t_data *data)
{
	char	*home;
	char	*old_path;

	old_path = get_curr_path(0);
	home = env_grepvalue("HOME");
	if (home == NULL)
	{
		custom_err("cd", "", "HOME not set", 1);
		free (old_path);
		return (0);
	}
	if (chdir(home) == 0)
	{
		env_export("OLD_PWD", old_path);
		env_export("PWD", home);
		free (data->pwd);
		data->pwd = _strdup(home);
	}
	free (old_path);
	return (1);
}

int	cd(char **argv)
{
	t_data	*data;
	char	*old_path;

	data = data_hook(NULL);
	if (argv && (argv[1] == NULL || str_equal(argv[1], "~")))
		return (go_to_home(data));
	old_path = get_curr_path(0);
	if (is_fod(argv[1]) == _FILE)
	{
		free (old_path);
		do_error(NOTDIRECTORY_ERR, "cd", argv[1]);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		free (old_path);
		do_error(NSFODIR_ERR, "cd", argv[1]);
		return (1);
	}
	free (data->pwd);
	data->pwd = get_curr_path(1);
	env_export("PWD", data->pwd);
	env_export("OLD_PWD", old_path);
	return (free(old_path), 1);
}
