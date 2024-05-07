/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/07 19:18:10 by aabouqas         ###   ########.fr       */
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

int	cd(char **argv)
{
	char	*curr_path;
	char	*old_path;

	old_path = get_curr_path();
	if (argv[1] == NULL || is_io_op(argv[1]))
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
	if (is_fod(argv[1]) == _FILE)
		return (do_error(NOTDIRECTORY_ERR, argv[1]), 1);
	if (chdir(argv[1]) != 0)
		return (do_error(NSFODIR_ERR, argv[1]), 1);
	curr_path = get_curr_path();
	env_export("PWD", curr_path);
	env_export("OLD_PWD", old_path);
	free (curr_path);
	free (old_path);
	return (1);
}
