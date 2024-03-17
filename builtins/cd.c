/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/17 23:18:01 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_dir_name(char *path)
{
	return (ft_strrchr(path, '/'));
}

int	cd(char *dir_name)
{
	return (chdir(dir_name));
}
