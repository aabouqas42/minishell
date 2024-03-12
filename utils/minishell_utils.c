/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/12 17:21:53 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

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
	program = ft_strjoin("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], program);
		if (access(cmd_path, X_OK) == 0)
			return (free(cmd_path), free (program), i);
		free(cmd_path);
		i++;
	}
	free (program);
	return (-1);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
