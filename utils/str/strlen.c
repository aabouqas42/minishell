/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:20:14 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/27 01:45:12 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	_strlen(char *str, char c)
{
	size_t	size;

	size = 0;
	while (str && str[size] && str[size] != c)
		size++;
	return (size);
}
