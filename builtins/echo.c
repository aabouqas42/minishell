/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/19 10:40:26 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo()
{
	int	i;
	int	nl;
	t_data *data;
	
	i = 1;
	nl = 1;
	data = data_hook(NULL);
	if (data->commands[i] && is_same(data->commands[i], "-n"))
		(nl = 0, i++);
	while (data->commands[i])
	{
		printf("%s", data->commands[i]);
		i++;
		if (data->commands[i])
			printf(" ");
	}
	if (nl == 0)
		printf("%%");
	printf("\n");
}
