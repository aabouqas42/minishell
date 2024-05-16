/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 08:54:08 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/16 16:53:45 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	strnum(char *s)
{
	int	i;

	i = 0;
	if (s && _strchr("+-", *s))
		s++;
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
	char	**av;

	av = cmd->argv;
	if (av[1] == NULL)
	{
		print(1, "exit", 1);
		safe_exit(0);
	}
	if ((strnum(av[1]) == 0 && get_argsc(av) >= 2)
		|| (ft_atoi(av[1]) == -1 && av[1][0] != '-'))
	{
		print(1, "exit", 1);
		custom_err(av[0], av[1], "numeric argument required", 255);
		safe_exit(data_hook(NULL)->exit_status);
	}
	else if (get_argsc(av) > 2)
	{
		custom_err(av[0], "", "too many arguments", 1);
		return ;
	}
	safe_exit(ft_atoi(av[1]));
}
