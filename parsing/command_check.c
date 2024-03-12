/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/12 17:10:04 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_cmd(char **paths, char *cmd, char **dest)
{
	char	*tmp;
	int		status;
	size_t	i;

	if (paths == NULL || cmd == NULL || *paths == NULL)
		return (0);
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
	}
	free(tmp);
	return (CMD_INVALID);
}