/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 15:30:07 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_curr_path(void)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
		return data_hook(NULL)->pwd;
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
	if (argv[1] == NULL || is_io_op(argv[1]))
		return (go_to_home(data, old_path, curr_path));
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
	curr_path = get_curr_path();
	env_export("PWD", curr_path);
	env_export("OLD_PWD", old_path);
	return (free (curr_path), free (old_path), 1);
}
