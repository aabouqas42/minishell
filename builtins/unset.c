/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:48:44 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 11:49:21 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset(char **argv)
{
	t_data	*data;

	data = data_hook(NULL);
	while (argv && *argv)
	{
		if (env_valid_name(*argv))
			env_unset(*argv, &data->env);
		else
			do_error(INVNAMEENV_ERR, "unset", *argv);
		argv++;
	}
	return (0);
}
