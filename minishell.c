/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:23:51 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/12 17:32:21 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *paths;
	char	*cmd;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", ft_strlen(*env)) != NULL)
		{
			paths = *env+5;
			break;
		}
		env++;
	}
	// if ( == CMD_VALID)
		// ft_printf("%s is valid\n", cmd);
	// else
		// ft_printf("%s is invalid\n", cmd);
	printf("^%d^", is_valid_cmd(env, av[1], &cmd));
	return (EXIT_SUCCESS);
}
