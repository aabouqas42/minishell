/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 16:36:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path(void)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
		return (data_hook(NULL)->pwd);
	return (curr_path);
}

int	go_to_home(t_data *data, char *old_path, char *curr_path)
{
	char	*home;

	home = env_grepvalue("HOME");
	if (home == NULL)
	{
		custom_err("cd", "", "HOME not set", 1);
		return (0);
	}
	if (chdir(home) == 0)
	{
		env_export("OLD_PWD", old_path);
		env_export("PWD", curr_path);
		free (data->pwd);
		data->pwd = curr_path;
	}
	free (old_path);
	return (1);
}

int	cd(char **argv)
{
	t_data	*data;
	char	*curr_path;
	char	*old_path;

	curr_path = NULL;
	data = data_hook(NULL);
	old_path = get_curr_path();
	if (argv && argv[1] == NULL)
		return (go_to_home(data, old_path, curr_path));
	if (is_fod(argv[1]) == _FILE)
	{
		// free (old_path);
		do_error(NOTDIRECTORY_ERR, "cd", argv[1]);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		// free (old_path);
		do_error(NSFODIR_ERR, "cd", argv[1]);
		return (1);
	}
	data->pwd = get_curr_path();
	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
	{
		//IMTIIIWN N GETCWD
		print(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 1);
		// printf("CURRPATH[NULL] : %s\n", data->pwd);
		curr_path = _strjoin(data->pwd, "/");
		data->pwd = _strjoin(curr_path, argv[1]);
	}
	// printf("CURRPATH : %s\n", curr_path);
	// printf("PWDPATH : %s\n", curr_path);
	env_export("PWD", data->pwd);
	env_export("OLD_PWD", old_path);
	return (1);
}
