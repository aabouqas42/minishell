/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/10 17:03:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_flag(char *flag)
{
	size_t	i;

	if (flag == NULL || *flag == '\0')
		return (0);
	i = flag[0] == '-';
	while (flag && flag[i] && flag[i] == 'n')
		i++;
	return (i == _strlen(flag));
}

void	echo(char **argv)
{
	int		i;
	int		new_line;
	t_data	*data;

	i = 1;
	new_line = 1;
	data = data_hook(NULL);
	while (is_valid_flag(argv[i]))
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		print(1, argv[i], 0);
		i++;
		if (argv[i])
			print(1, " ", 0);
	}
	if (new_line)
		print(1, "\n", 0);
}
