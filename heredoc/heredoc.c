/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:53:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 13:53:27 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_heredoc(char *target)
{
	t_data	*data;
	char	*in;

	data = data_hook(NULL);
	while (1)
	{
		in = readline("heredoc > ");
		if (in && is_same(in, target))
			break ;
		data->heredoc = _strjoin(data->heredoc, in);
		data->heredoc = _strjoin(data->heredoc, "\n");
	}
}
