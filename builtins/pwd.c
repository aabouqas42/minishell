/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/12 10:56:59 by mait-elk         ###   ########.fr       */
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
		custom_err("pwd", "getcwd", "Unexpected Error", 255);
		return (-1);
	}
	print(1, pwd, 1);
	free(pwd);
	return (0);
}
