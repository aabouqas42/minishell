/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 08:54:08 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/11 10:53:43 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	strnum(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	__exit(t_cmd *cmd)
{
	char	**argv;

	argv = cmd->argv;
	if (argv[1] == NULL)
	{
		print(1, "exit", 1);
		safe_exit(0);
	}
	if (strnum(argv[1]) == 0 && get_argsc(argv) >= 2)
	{
		print(1, "exit", 1);
		custom_err(argv[0], argv[1], "numeric argument required", 255);
		safe_exit(255);
	} else if (get_argsc(argv) > 2) {
		custom_err(argv[0], "", "too many arguments", 1);
		return ;
	}
	safe_exit(ft_atoi(argv[1]));
}
