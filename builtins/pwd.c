/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:06 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 15:29:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	print(1, working_dir, 1); // why you print it, before check ?
	if (working_dir == NULL)
		return (-1);
	free(working_dir);
	return (0);
}
