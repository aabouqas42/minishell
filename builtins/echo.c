/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/18 03:04:44 by mait-elk         ###   ########.fr       */
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
	if (argv && argv[i])
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0 && ft_strlen(argv[i]) == 2)
			(nl = 0, i++);
		while (argv[i])
		{
			if (argv[i][0] == '$')
				ft_printf("%s", (env_valueof(argv[i], data)) ? env_valueof(argv[i], data) : "");
			else
				printf("%s", argv[i]);
			i++;
		}
	}
	if (nl)
		printf("\n");
}
