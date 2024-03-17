/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/17 16:13:39 by mait-elk         ###   ########.fr       */
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
		wc += (*rdline != '\0');
		while (*rdline && (*rdline != ' ' || found_dqt))
		{
			ft_switch_binary(&found_dqt, (*rdline == '\"'));
			rdline++;
		}
	}
	return (wc);
}

char	**ft_split_argv(char *rdline)
{
	int		found_dqt;
	// char	**argv;
	size_t	wc;
	size_t	i;

	i = 0;
	wc = ft_split_argv_counter(rdline);
	found_dqt = 0;
	while (rdline && *rdline)
	{
		while (*rdline == ' ')
			rdline++;
		wc += (*rdline != '\0'); // FOUND ANOTHER WORD
		while (*rdline && (*rdline != ' ' || found_dqt)) // WHILE *rdline != SPACE OR IM WOKING INSIDE DOUBLE QUOTES vvvv
		{
			printf("%c", *rdline);
			ft_switch_binary(&found_dqt, (*rdline == '\"')); // IF FOUND_DQT == 1 // THEN IM WORKING INSIDE DOUBLE QUOTES LIKE "hello world"
			rdline++;
		}
		if (found_dqt)
			(printf("error \n"), exit(0)); //FOUND UNCLOSED DOUBLE QUOTES //THEN ERROR
		if (*rdline != '\0') printf("\n"); //NEW WORD NL
	}
	return (NULL);
}
