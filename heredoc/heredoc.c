/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:53:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 19:52:10 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_heredoc(char *target)
{
	t_data	*data;
	char	*in;

	data = data_hook(NULL);
	data->heredoc = NULL;
	printf("open heredoc :) %s\n", target);
	in = readline("heredoc 1> ");
	while (!is_same(in, target))
	{
		data->heredoc = _strjoin(data->heredoc, in);
		data->heredoc = _strjoin(data->heredoc, "\n");
		in = readline("heredoc 2> ");
	}
}
