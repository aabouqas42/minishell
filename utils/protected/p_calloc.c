/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_calloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:48:03 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/27 00:58:31 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*p_calloc(size_t size)
{
	char	*res;

	res = malloc(size);
	if (res == NULL)
		safe_exit(-1);
	while (size--)
		res[size] = '\0';
	return ((void *)res);
}
