/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:51:43 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/18 12:52:40 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*_strnjoin(char *str1, char *str2, size_t size)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = _nsx_strlen(str1) + size;
	str = malloc (len + 1);
	if (str == NULL)
		return (free (str1), safe_exit(-1), NULL);
	i = 0;
	while (str1 && str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (str2 && *str2 && size)
	{
		str[i] = *str2;
		i++;
		str2++;
		size--;
	}
	str[i] = '\0';
	return (free (str1), str);
}
