/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strskp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:59:07 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/24 15:06:24 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strskps(char *str, char *to_skip)
{
	while (str && ft_strchr(to_skip, *str))
		str++;
	return (str);
}

int	ft_strskpi(char *str, char *to_skip)
{
	int	i;

	i = 0;
	while (str && ft_strchr(to_skip, str[i]))
		i++;
	return (i);
}

size_t	ft_strskpul(char *str, char *to_skip)
{
	size_t	i;

	i = 0;
	while (str && ft_strchr(to_skip, str[i]))
		i++;
	return (i);
}