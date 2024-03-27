/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dqt_sqt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:44:17 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/27 02:07:56 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_size(char *str)
{
	size_t	size;
	int		dqt;
	int		sqt;

	size = 0;
	dqt = 0;
	sqt = 0;
	while (str && *str)
	{
		if (*str == '\"' && sqt == 0)
			dqt = !dqt;
		if (*str == '\'' && dqt == 0)
			sqt = !sqt;
		if ((dqt && *str != '\"') || (sqt && *str != '\'') || (ft_strchr("\'\"", *str) == NULL && !dqt && !sqt))
			size++;
		str++;
	}
	return (size);
}

char	*handle_dqt_sqt(char *str)
{
	size_t	size;
	int		dqt;
	int		sqt;
	int		i;
	char	*new_str;
	char	*saved_pointer;

	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		return (str);
	size = get_size(str);
	// printf("str : %s\nsize : %zu\n", str, size);
	saved_pointer = str;
	new_str = p_calloc (size + 1);
	if (new_str == NULL)
		safe_exit(-1);
	i = 0;
	dqt = 0;
	sqt = 0;
	while (str && *str)
	{
		if (*str == '\"' && sqt == 0)
			dqt = !dqt;
		if (*str == '\'' && dqt == 0)
			sqt = !sqt;
		if ((dqt && *str != '\"') || (sqt && *str != '\'') || (ft_strchr("\'\"", *str) == NULL && !dqt && !sqt))
			new_str[i++] = *str;
		str++;
	}
	free (saved_pointer);
	return (new_str);
}
