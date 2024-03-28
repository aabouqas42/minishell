/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:12:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/27 18:42:06 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**_realloc(char **old_tab, char *to_append)
{
	char	**new_tab;
	size_t	tab_len;
	size_t	i;

	if (old_tab == NULL)
	{
		new_tab = p_calloc( 2 * sizeof(char *));
		new_tab[0] = to_append;
		return (new_tab);
	}
	tab_len = 0;
	while (old_tab[tab_len])
		tab_len++;
	new_tab = p_calloc((tab_len + 2) * sizeof(char *));
	i = 0;
	while (i < tab_len)
	{
		new_tab[i] = _strdup(old_tab[i]);
		free (old_tab[i]);
		i++;
	}
	new_tab[i] =_strdup(to_append);
	free (old_tab[i]);
	return (new_tab);
}
