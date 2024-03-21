/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:33 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/21 14:49:59 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char **argv)
{
	if (argv[1] == NULL)
		return (chdir(getenv("HOME")));
	if (chdir(argv[1]) != 0)
		printf("no such file or directory: %s\n", argv[1]);
	return (1);
}
