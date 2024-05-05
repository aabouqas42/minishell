/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:53:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 18:22:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_heredoc(char *target)
{
	t_data	*data;
	char	*in;

	data = data_hook(NULL);
	data->heredoc = NULL;
	while (1)
	{
		in = readline("heredoc 1> ");
		if (is_same(in, target))
			break ;
		data->heredoc = _strjoin(data->heredoc, in);
		data->heredoc = _strjoin(data->heredoc, "\n");
	}
}
