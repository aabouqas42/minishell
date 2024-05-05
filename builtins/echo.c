/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/04 15:24:04 by mait-elk         ###   ########.fr       */
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
	return (i == _strlenc(flag, '\0'));
}

void	echo(void)
{
	int		i;
	int		new_line;
	t_data	*data;

	i = 1;
	new_line = 1;
	data = data_hook(NULL);
	if (is_valid_flag(data->args[1]))
	{
		new_line = 0;
		i++;
	}
	while (data->args[i])
	{
		print(1, data->args[i], 0);
		i++;
		if (data->args[i])
			print(1, " ", 0);
	}
	if (new_line)
		print(1, "\n", 0);
}
