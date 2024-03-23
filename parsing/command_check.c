/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/23 15:41:32 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_paths_env()
{
	char	*paths;

	paths = getenv("PATH");
	if (_nsx_strlen(paths) > 0)
		return (paths);
	return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
}

char	*get_program_path(t_data *data, char *cmd)
{
	char	*program_path;

	(void)data;
	program_path = ft_strdup(cmd);
	if (program_path == NULL)
		safe_exit(-1);
	return (program_path);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	*tmp;
	char	*paths;
	char	*program_path;
	char	c;
	size_t	i;

	if (cmd == NULL)
		return (CMD_FAIL);
	if (access(cmd, X_OK) == 0)
		return (data->program_path = get_program_path(data, cmd), 1);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		safe_exit(-1);
	paths = env_grepvalue("PATH");
	while (paths && *paths)
	{
		i = 0;
		while (paths[i] && paths[i] != ':')
			i++;
		c = paths[i];
		paths[i] = '\0';
		program_path = ft_strjoin(paths, tmp);
		paths[i] = c;
		if (program_path == NULL)
			(free(tmp), safe_exit(-1));
		if (access(program_path, X_OK) == 0)
			return (data->program_path = program_path, free(tmp), CMD_VALID);
		free(program_path);
		paths[i] = ':';
		paths += i + (paths[i] == ':');
	}
	free(tmp);
	return (CMD_INVALID);
}
