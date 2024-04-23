/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/23 19:30:36 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_program_path(char *cmd)
{
	char	*program_path;

	program_path = _strdup(cmd);
	if (program_path == NULL)
		safe_exit(-1);
	data_hook(NULL)->program_path = program_path;
}

int	is_dir(char *name)
{
	DIR	*dir;

	dir = opendir(name);
	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	*tmp;
	char	*paths;
	char	*program_path;
	char	c;
	size_t	i;

	#error	working in this file 2023-04-23
	if (cmd == NULL || is_dir(cmd))
		return (do_error(ISDIR_ERR, cmd), 0);
	if (access(cmd, X_OK) == 0)
		return (get_program_path(cmd), 1);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		safe_exit(-1);
	paths = env_grepvalue("PATH");
	while (paths && *paths)
	{
		i = _strlenc(paths, ':');
		c = paths[i];
		paths[i] = '\0';
		program_path = ft_strjoin(paths, tmp);
		paths[i] = c;
		if (program_path == NULL)
			(free(tmp), safe_exit(-1));
		if (access(program_path, X_OK) == 0)
			return (data->program_path = program_path, free(tmp), 1);
		free(program_path);
		paths += i + (paths[i] == ':');
	}
	return (free(tmp), do_error(COMDNF_ERR, cmd), 0);
}
