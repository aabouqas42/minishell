/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/31 03:01:48 by mait-elk         ###   ########.fr       */
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
	if (data->commands[i] && _strcmp(data->commands[i], "-n") == 0)
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
