/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/23 14:21:04 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd()
{
	char	*working_dir;

	t_data *data = data_hook(NULL);

	printf("<<%s>>\n", data->line);
	working_dir = getcwd(NULL, 0);
	printf("%s\n", working_dir);
	if (working_dir == NULL)
		return (-1);
	free(working_dir);
	return (0);
}
