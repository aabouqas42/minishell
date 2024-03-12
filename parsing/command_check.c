/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/12 13:18:51 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_command(char **paths, char *command)
{
	char	*tmp;
	int		status;
	size_t	i;

	if (paths == NULL || command == NULL || *paths == NULL)
		return (0);
	i = 0;
	tmp = ft_strjoin("/", command);
	if (tmp == NULL)
		return (0);
	while (paths[i])
	{
		free(command);
		command = ft_strjoin(paths[i], tmp);
		if (command == NULL)
			return (0);
		if (access(command, X_OK) == 0)
			return (free(command), 1);
		free(command);
	}
}