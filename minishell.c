/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:23:51 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/12 13:12:38 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *paths;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", ft_strlen(*env)) != NULL)
		{
			paths = *env+5;
			break;
		}
		env++;
	}
	ft_printf("%s\n",  ft_split(paths, ':')[0]);
	return (EXIT_SUCCESS);
}
