/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:53:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/06 20:33:05 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand(char *str)
{
	char	*new_str;
	size_t	i;

	if (!_strchr(str, '$'))
		return (str);
	i = 0;
	new_str = NULL;
	while (str && str[i] != '\0')
	{
		if (str[i] == '$')
			i += set_var(&str[i + 1], &new_str);
		else
			new_str = _strnjoin(new_str, &str[i], 1);
		i++;
	}
	// hello $USER hhhh this is a test
	free (str);
	return (new_str);
}

int	open_heredoc(t_arg *target)
{
	t_data	*data;
	char	*in;
	char	*tmp;
	int		fd_in;
	int		fd_out;

	data = data_hook(NULL);
	tmp = target->value;
	target->value = expand_arg(tmp, 1);
	free(tmp);
	// printf("open heredoc :) %s\n", target);
	unlink("/tmp/minishell_heredoc");
	//check open if fails
	fd_out = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY, 0x777);
	fd_in = open("/tmp/minishell_heredoc", O_RDONLY);
	unlink("/tmp/minishell_heredoc");
	in = readline("heredoc > ");
	while (!is_same(in, target->value))
	{
		if (target->type != ARG_QT)
			in = expand(in);
		print(fd_out, in, 1);
		in = readline("heredoc > ");
	}
	close(fd_out);
	return (fd_in);
}
