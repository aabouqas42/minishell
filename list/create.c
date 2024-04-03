/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:36:40 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/03 01:43:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list_args	*create(char )
{
	t_list_args	*new_node;

	new_node->_in = 0;
	new_node->_out = 1;
	new_node->action = Void;
	
	return (new_node);
}
