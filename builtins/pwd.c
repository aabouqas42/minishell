/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 14:34:51 by mait-elk         ###   ########.fr       */
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
		return (print(1, env_grepvalue("PATH"), 1), 1);
	print(1, pwd, 1);
	free(pwd);
	// printf("%s\n", data->pwd);
	return (0);
}
