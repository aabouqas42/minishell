/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/15 17:33:02 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd()
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	if (working_dir == NULL)
		return (-1);
	printf("%s\n", working_dir);
	free(working_dir);
	return (0);
}
