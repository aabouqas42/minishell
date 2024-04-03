/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:pipes/pipe.c
/*   Created: 2024/04/01 05:26:50 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/02 17:55:53 by mait-elk         ###   ########.fr       */
=======
/*   Created: 2024/04/03 00:51:00 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/03 00:54:50 by aabouqas         ###   ########.fr       */
>>>>>>> 99b709dcd01e9713c2110733d2085167e0a9414e:list/get_data.c
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_list_args	*get_last(t_list_args *head)
{
	t_list_args	*last_node;

	if (head == NULL)
		return (NULL);
	last_node = head;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

t_list_args	*get_first()
{
	return (data_hook(NULL)->list);
}

