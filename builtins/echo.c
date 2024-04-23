/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/23 09:53:43 by mait-elk         ###   ########.fr       */
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
	if (data->args[i] && is_same(data->args[i], "-n"))
		(nl = 0, i++);
	while (data->args[i])
	{
		printf("%s", data->args[i]);
		i++;
		if (data->args[i])
			printf(" ");
	}
	if (nl == 0)
		printf("%%");
	printf("\n");
}
