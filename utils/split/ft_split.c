/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/26 03:41:52 by aabouqas         ###   ########.fr       */
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

char	**_split(char *str)
{
	char	**argv;
	size_t	size;
	size_t	i;
	int		dqt;
	size_t	wc;

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
			// if (str[size] == '\"')
				// dqt = (dqt == 0);
			if (ft_strchr("\"\'", str[size]) != NULL)
				dqt = (dqt == 0);
			size++;
		}
		str[size] = '\0';
		argv[i++] = _strndup(str);
		str += size + 1;
	}
	return (argv);
}
