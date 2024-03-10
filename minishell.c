/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:23:51 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/10 20:38:47 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	while (1)
	{
		char *line = readline(">> ");
		printf("\n[%s]\n", line);
		free (line);
	}
}
