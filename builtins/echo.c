/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/23 15:45:26 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_data *data)
{
	int	i;
	int	nl;
	
	i = 1;
	nl = 1;
	if (data->argv[i] && _strcmp(data->argv[i], "-n") == 0)
		(nl = 0, i++);
	while (data->argv[i])
	{
		printf("%s", data->argv[i]);
		i++;
		if (data->argv[i])
			printf(" ");
	}
	if (nl == 0)
		printf("%%");
	printf("\n");
}
