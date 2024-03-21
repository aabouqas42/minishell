/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/21 16:59:36 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_paths_env(t_data *data)
{
	char	*paths;

	paths = getenv("PATH");
	if (_nsx_strlen(paths) > 0)
		return (paths);
	return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
}

char	*get_program_path(t_data *data, char *cmd)
{
	char	*program_path;

	program_path = ft_strdup(cmd);
	if (program_path == NULL)
	{
		_free(data);
		exit(-1);
	}
	return (program_path);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	*tmp;
	char	*paths;
	char	*program_path;
	size_t	i;

	if (cmd == NULL)
		return (CMD_FAIL);
	if (access(cmd, X_OK) == 0)
		return (data->program_path = get_program_path(data, cmd), 1);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		return (_free(data), exit(-1), CMD_FAIL);
	paths = env_grepvalue("PATH", data);
	while (paths && *paths)
	{
		i = 0;
		while (paths[i] && paths[i] != ':')
			i++;
		paths[i] = '\0';
		program_path = ft_strjoin(paths, tmp);
		if (program_path == NULL)
			return (free(tmp), _free(data), exit(-1), CMD_FAIL);
		if (access(program_path, X_OK) == 0)
			return (data->program_path = program_path, free(tmp), CMD_VALID);
		free(program_path);
		paths[i] = ':';
		paths += i + (paths[i] == ':');
	}
	return (CMD_INVALID);
}
