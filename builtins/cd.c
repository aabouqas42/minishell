/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 20:03:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path(void)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
	{
		print(1, "minishell-init: error retrieving current \
directory: getcwd: cannot access parent directories: \
No such file or directory", 1);
		return (data_hook(NULL)->pwd);
	}
	return (curr_path);
}

int	go_to_home(t_data *data)
{
	char	*home;
	char	*old_path;

	old_path = get_curr_path();
	home = env_grepvalue("HOME");
	if (home == NULL)
	{
		custom_err("cd", "", "HOME not set", 1);
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
	char	*curr_path;
	char	*old_path;

	data = data_hook(NULL);
	if (argv && (argv[1] == NULL || is_same(argv[1], "~")))
		return (go_to_home(data));
	old_path = get_curr_path();
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
	// free (data->pwd);
	// data->pwd = get_curr_path();
	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
	{
		//IMTIIIWN N GETCWD
		// print(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 1);
		// printf("CURRPATH[NULL] : %s\n", data->pwd);
		curr_path = _strjoin(data->pwd, "/");
		data->pwd = _strjoin(curr_path, argv[1]);
	}
	else
		data->pwd = curr_path;
	env_export("PWD", data->pwd);
	env_export("OLD_PWD", old_path);
	return (1);
}
