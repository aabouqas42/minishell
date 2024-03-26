/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/26 01:31:03 by mait-elk         ###   ########.fr       */
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
