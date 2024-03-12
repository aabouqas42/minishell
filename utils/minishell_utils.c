/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/12 12:01:36 by aabouqas         ###   ########.fr       */
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
	char	*program;
	int		i;

	i = 0;
	while (paths[i])
	{
		program = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(paths[i], program);
		free(program);
		if (access(cmd_path, X_OK) == 0)
			return (free(cmd_path), i);
		i++;
	}
	return (0);
}
