/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/27 09:12:49 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_last_exit(char **str)
{
	t_data	*data;
	char	*exit_status;

	data = data_hook(NULL);
	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		safe_exit(-1);
	*str = _strnjoin(*str, exit_status, _strlenc(exit_status, '\0'));
	if (*str == NULL)
		safe_exit(-1);
	data->exit_status = 0;
	return (0);
}

int	set_var(char *argv_str, char **str)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	if (*argv_str == '?')
		return (set_last_exit(str), 1);
	if (ft_isdigit(argv_str[0]))
		return (1);
	while (argv_str[i] && (ft_isalnum(argv_str[i]) || argv_str[i] == '_'))
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	tmp = env_grepvalue(argv_str);
	argv_str[i] = c;
	if (tmp != NULL)
	{
		*str = _strnjoin(*str, tmp, _strlenc(tmp, '\0'));
	}
	return (i);
}

// char	*_expander(char *str)
// {
// 	char	*res;
// 	int		sqt;

// 	if (str == NULL)
// 		return (NULL);
// 	res = NULL;
// 	sqt = 0;
// 	while (*str)
// 	{
// 		if (*str == 1)
// 			sqt = (sqt == 0);
// 		if (*str == '$' && (ft_isalnum(*(str +1))
// 				|| *(str +1) == 1 || *(str +1) == 2) && sqt == 0)
// 			(1) && (str++, str += set_var(str, &res));
// 		else if (ft_isprint(*str))
// 			res = _strnjoin(res, str++, 1);
// 		else
// 			str++;
// 	}
// 	return (res);
// }
