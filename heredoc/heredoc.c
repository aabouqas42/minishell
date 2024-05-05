/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:53:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/05 12:18:08 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_heredocs(t_cmd *cmds)
{
	t_data	*data;
	char	*save;
	size_t	i;
	size_t	j;

	i = 0;
	data = data_hook(NULL);
	while (cmds[i].argv)
	{
		j = 0;
		while (cmds[i].argv[j])
		{
			save = cmds[i].argv[j];
			// cmds[i].argv[j] = NULL;
			// if (check_redirections(cmds[i].argv))
			// 	data_hook(NULL)->syn_err = 1;
			// cmds[i].argv[j] = save;
			//check syntax :(
			if (is_io_op(cmds[i].argv[j]) && (cmds[i].argv[j +1] == NULL || is_io_op(cmds[i].argv[j +1])))
			{
				data_hook(NULL)->syn_err = 1;
				return ;
			}
			// printf("[%s] {%d}\n", save, data_hook(NULL)->syn_err);
			if (is_same(cmds[i].argv[j], "<<"))
			{
				// printf("%d\n", check_redirections(cmds[i].argv));
				// open_heredoc(cmds[i].argv[j]);
				printf("%s EOF\n", cmds[i].argv[j +1]);
			}
			j++;
		}
		i++;
	}
}

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
