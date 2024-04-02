/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:29:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/02 06:50:24 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "include/minishell.h"

int main(int ac, char **av)
{
	int pid;
	int	i = 1;
	int	fds[2];

	pipe(fds);
	while (av[i +1])
	{
		// printf("%s\n", av[i]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fds[1], 1);
			close(fds[0]);
			close(fds[1]);
			char	**v = ft_split(av[i], ' ');
			execve(v[0], v, NULL);
		}
		// waitpid(pid, NULL, 0);
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
		char	**v = ft_split(av[i], ' ');
		execve(v[0], v, NULL);
	}
	close(fds[0]);
	close(fds[1]);
	// waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);	
}
