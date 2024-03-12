/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:23:51 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/12 17:12:26 by mait-elk         ###   ########.fr       */
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
	if (is_valid_cmd(ft_split(paths, ':'), av[1]) == CMD_VALID)
		ft_printf("%s is valid\n", av[1]);
	else
		ft_printf("%s is invalid\n", av[1]);
	return (EXIT_SUCCESS);
}
