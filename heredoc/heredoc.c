/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:53:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/16 11:07:32 by aabouqas         ###   ########.fr       */
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
		if (str[i] == '$'
			&& (ft_isalnum(str[i + 1]) || _strchr("_?", str[i + 1])))
			i += set_var(&str[i + 1], &new_str);
		else
			new_str = _strnjoin(new_str, &str[i], 1);
		i++;
	}
	free (str);
	return (new_str);
}

void	_close(int in, int out)
{
	close (in);
	close(out);
	safe_exit(-1);
}

int	open_heredoc(t_arg *target)
{
	t_data	*data;
	char	*in;
	int		fd_in;
	int		fd_out;

	data = data_hook(NULL);
	unlink("/tmp/minishell_heredoc");
	fd_out = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY, 0x777);
	fd_in = open("/tmp/minishell_heredoc", O_RDONLY);
	unlink("/tmp/minishell_heredoc");
	if (fd_in == -1 || fd_out == -1)
		_close(fd_in, fd_out);
	in = readline("heredoc > ");
	while (in && str_equal(in, target->value) == 0)
	{
		if (target->type != ARG_QT)
			in = expand(in);
		print(fd_out, in, 1);
		free(in);
		in = readline("heredoc > ");
	}
	free(in);
	close(fd_out);
	return (fd_in);
}
