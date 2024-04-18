/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:12:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/18 16:36:43 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_io_op(char	*str)
{
	if (str == NULL)
		return (1);
	return (
		(ft_strchr("<>|", *str) && *(str + 1) == 0)
		|| ft_strncmp(str, ">>", 3) == 0
		|| ft_strncmp(str, "<<", 3) == 0
	);
}

char	**_realloc(char **old_tab, char *to_append)
{
	char	**new_tab;
	size_t	tab_len;
	size_t	i;

	if (to_append == NULL || *to_append == '\0')
		return (old_tab);
	if (old_tab == NULL)
	{
		new_tab = p_calloc(2 * sizeof(char *));
		*new_tab = to_append;
		return (new_tab);
	}
	tab_len = 0;
	while (old_tab[tab_len])
		tab_len++;
	new_tab = p_calloc((tab_len + 2) * sizeof(char *));
	i = 0;
	while (i < tab_len)
	{
		new_tab[i] = old_tab[i];
		i++;
	}
	free(old_tab);
	new_tab[i] = to_append;
	return (new_tab);
}

int	_spaces(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
