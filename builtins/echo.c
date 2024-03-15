/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:44:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/14 18:12:51 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(char *line)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	while (*line == ' ')
		line++;
	if (*line == '-')
		if (ft_strnstr(line, "-n", ft_strlen(line)))
			(j = 0, line += 2);
	while (*line == ' ')
		line++;
	while (line[i])
	{
		if (line[i] == '\\' && line[i+1] != '\0')
			printf("%c", line[i+1]);
		else if (line[i] != '\"' && line[i] != '\'')
			printf("%c", line[i]);
		i++;
	}
	if (j)
		printf("\n");
	return (0);
}