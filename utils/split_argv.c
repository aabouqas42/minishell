/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/15 17:39:16 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void ft_switch_binary(int *b, int condition)
{
	if (condition)
		*b = (*b == 0);
}

size_t	ft_split_argv_counter(char *rdline)
{
	size_t	wc;
	int		found_dqt;

	wc = 0;
	found_dqt = 0;
	while (rdline && *rdline)
	{
		while (*rdline == ' ')
			rdline++;
		while (*rdline && (*rdline != ' ' || found_dqt))
		{
			ft_switch_binary(&found_dqt, (*rdline == '\"'));
			rdline++;
		}
		wc += (*rdline != '\0');
	}
	return (wc);
}

char	**ft_split_argv(char *rdline)
{
	char	**argv;
	size_t	wc;
	size_t	i;

	i = 0;
	wc = ft_split_argv_counter(rdline);
	while (i < wc)
	{
		while (*rdline == ' ')
			rdline++;
		printf("%s\n", rdline);
		while (*rdline && *rdline != ' ')
			rdline++;
		i++;
	}
	return (argv);
}
