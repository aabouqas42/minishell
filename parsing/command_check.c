/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/14 15:44:53 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_paths_env(t_data *data)
{
	char	*paths;

	paths = getenv("PATH");
	if (paths)
		return (paths);
	_free(data);
	exit(-1);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	*tmp;
	char	*cm;
	size_t	i;

	if (data->env == NULL || cmd == NULL)
		return (CMD_FAIL);
	if (access(cmd, X_OK) == 0)
		return (data->program_path = cmd, CMD_VALID);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		return (exit(-1), CMD_FAIL);
	i = 0;
	while (data->paths[i])
	{
		cm = ft_strjoin(data->paths[i], tmp);
		if (cm == NULL)
			return (free(tmp), exit(-1), CMD_FAIL);
		if (access(cm, X_OK) == 0)
			return (data->program_path = cm, free(tmp), CMD_VALID);
		free(cm);
		i++;
	}
	return (CMD_INVALID);
}
