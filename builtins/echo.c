/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/21 14:02:25 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_data *data)
{
	char	**argv;
	int		i;
	int		nl;

	i = 1;
	nl = 1;
	argv = data->argv;
	if (argv && ft_strncmp(argv[i], "-n", 3))
		(nl = 0, i++);
	if (argv && argv[i])
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			i++;
		}
	}
	if (nl)
		printf("\n");
}
