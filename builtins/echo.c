/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/21 14:09:49 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_data *data)
{
	int	i;
	int	nl;
	
	i = 1;
	nl = 1;
	if (ft_strncmp(data->argv[i], "-n", 3) == 0)
		(nl = 0, i++);
	while (data->argv[i])
	{
		printf("%s", data->argv[i]);
		i++;
		if (data->argv[i])
			printf(" ");
	}
	if (nl)
		printf("%%\n");
	else
		printf("\n");
}
