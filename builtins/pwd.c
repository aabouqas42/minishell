/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 19:23:06 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	if (working_dir == NULL)
		return (-1);
	print(1, working_dir, 1);
	free(working_dir);
	return (0);
}
