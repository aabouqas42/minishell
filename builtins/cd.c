/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/13 16:01:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_dir_name(char *path)
{
	return (ft_strrchr(path, '/'));
}

int	cd(char *dir_name)
{
	char	*wd;
	char	*temp;
	char	*path;
	if (dir_name == NULL)
		return (-1);
	dir_name += *dir_name == '"';
	if (ft_strrchr(dir_name, '"') != NULL)
		*ft_strrchr(dir_name, '"') = '\0';
	if (get_dir_name(dir_name) != NULL)
		return (chdir(dir_name), 0);
	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (-1);
	temp = ft_strjoin(wd, "/");
	if (temp == NULL)
		return (free (wd), -1);
	path = ft_strjoin(temp, dir_name);
	if (path == NULL)
		return (free (wd), free (temp), -1);
	free (temp);
	if (chdir(path) != 0)
		printf("No such directory named %s\n", dir_name);
	free(path);
	free (wd);
	return (0);
}