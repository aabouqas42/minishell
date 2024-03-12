/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/12 17:33:29 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_paths_env(char	**env)
{
	if (env == NULL || *env == NULL)
		return (NULL);
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", ft_strlen(*env)))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

int	is_valid_cmd(char **env, char *cmd, char **dest)
{
	char	**paths;
	char	*tmp;
	size_t	i;

	paths = ft_split(get_paths_env(env), ':');
	if (paths == NULL || cmd == NULL || *paths == NULL)
		return (CMD_INVALID);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		return (CMD_FAIL);
	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], tmp);
		if (cmd == NULL)
			return (free(tmp), CMD_FAIL);
		if (access(cmd, X_OK) == 0)
			return (free(tmp), *dest = cmd, CMD_VALID);
		free(cmd);
		i++;
	}
	free(tmp);
	return (CMD_INVALID);
}
