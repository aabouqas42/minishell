/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 20:11:11 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	t_data	*data;
	char	*pwd;

	data = data_hook(NULL);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print(1, "pwd: error retrieving current \
directory: getcwd: cannot access parent directories: \
No such file or directory", 1);
		return (0);
	}
	print(1, pwd, 1);
	free(pwd);
	return (0);
}
