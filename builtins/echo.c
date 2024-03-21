/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/21 03:24:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_data *data)
{
	int	i;
	
	i = 1;
	if (ft_strncmp(data->argv[1], "-n", 2) == 0)
		i++;
	while (data->argv[i])
	{
		printf("%s", data->argv[i]);
		i++;
		if (data->argv[i])
			printf(" ");
	}
	if (ft_strncmp(data->argv[1], "-n", 2) != 0)
		printf("\n");
	else
		printf("%%\n");
	// char	**argv;
	// int		i;
	// int		nl;

	// i = 1;
	// nl = 1;
	// argv = data->argv;
	// if (argv && argv[i])
	// {
	// 	if (ft_strncmp(argv[i], "-n", 2) == 0 && ft_strlen(argv[i]) == 2)
	// 		(nl = 0, i++);
	// 	while (argv[i])
	// 	{
	// 		if (argv[i][0] == '$')
	// 		{
	// 			if (argv[i][1] == '?')
	// 			{
	// 				printf("%d ", data->exit_status >> 8);
	// 				data->exit_status = 0;
	// 			}else
	// 			{
	// 				t_env	*e;

	// 				e = env_get(argv[i], data);
	// 				if (e)
	// 					printf("%s ", e->value);
	// 			}
	// 		}
	// 		else
	// 			printf("%s", argv[i]);
	// 		i++;
	// 	}
	// }
	// if (nl)
	// 	printf("\n");
}
