/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/25 16:41:44 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_last_exit(char **str, t_data *data)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		safe_exit(-1);
	*str = _strjoin(*str, exit_status);
	return (0);
}

char	**_split(char *str, t_data *data)
{
	char	**argv;
	size_t	size;
	size_t	i;
	int		dqt;
	size_t	wc;

	(void)data;
	i = 0;
	dqt = 0;
	wc = argument_count(str);
	if (wc == 0)
		return (printf("Invalid Args..\n"), NULL);
	argv = p_calloc (sizeof(char *) * (wc + 1));
	while (i < wc)
	{
		size = 0;
		while (*str && *str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || dqt))
		{
			if (str[size] == '\"')
				dqt = (dqt == 0);
			size++;
		}
		argv[i] = _strndup(str, size);
		if (argv[i++] == NULL)
			return (argv[size] = NULL, NULL);
		str += size;
	}
	return (argv);
}
