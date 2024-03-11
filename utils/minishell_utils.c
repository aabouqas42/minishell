/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/11 18:37:19 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void	errexit(char *msg, void *to_free)
{
	free(to_free);
	exit(-1);
}

int	check_command(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (cmd_path == NULL)
			return (-1);
		if (access(cmd_path, X_OK) == 0)
			return (free (cmd_path), i);
		free (cmd_path);
		i++;
	}
	return (0);
}
