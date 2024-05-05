/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/05 13:27:35 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	close_unused_fds(int next)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->fds[1])
		close(data->fds[1]);
	if (data->oldfd)
		close(data->oldfd);
	if (next)
		data->oldfd = data->fds[0];
	else if (data->fds[0])
		close(data->fds[0]);
}

void	program_exec(char **args, int first, int next)
{
	t_data	*data;
	char	**argv;
	int		child_pid;

	data = data_hook(NULL);
	if (next)
		pipe(data->fds);
	child_pid = fork();
	if (child_pid == -1)
	{
		print(2, "Unexpected Error", 1);
		return ;
	}
	else if (child_pid == 0)
	{
		argv = get_argv(args);
		set_pipes(first, next);
		set_io();
		if (argv == NULL || is_valid_cmd(data, argv[0]) == 0)
			exit(127);
		init_env_array();
		execve(data->program_path, argv, data->env_2d);
		exit(errno);
	}
	close_unused_fds(next);
}

int	read_input(t_data *data)
{
	data->usrinput = readline(data->prompt);
	if (data->usrinput == NULL)
		safe_exit(1);
	if (*data->usrinput)
		add_history(data->usrinput);
	if (*data->usrinput == '\0')
	{
		free(data->usrinput);
		data->usrinput = NULL;
		return (-1);
	}
	return (1);
}

void	handle_input(t_data *data)
{
	int		index;
	// int		next;
	// t_flag	*ptr;

	if (is_valid_input() == 0)
	{
		free_tab(data->args);
		data->args = NULL;
		return ;
	}
	// ptr = data->flags;
	// if (data->cmds[1] == NULL && builtins())
	// 	return ;
	index = 0;
	data->oldfd = 0;
	// data->flags = ptr;
	// while (data->cmds && data->cmds[index])
	// {
	// 	next = data->cmds[index + 1] != NULL;
		// program_exec(data->cmds[index], index == 0, next);
	// 	data->flags += get_argsc(data->cmds[index]) + 1;
	// 	index++;
	// }
	// data->flags = ptr;
}

// #error problem in heredoc :)

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
	{
		print(2, "minishell : too many arguments", 1);
		return (get_argsc(av) * 1);
	}
	data_hook(&data);
	data_init(env);
	while (1)
	{
		if (read_input(&data) != -1)
		{
			handle_input(&data);
			// while (waitpid(-1, &data.exit_status, 0) != -1)
			// {
			// 	if (data.exit_status >> 8 == -1)
			// 		safe_exit(-1);
			// }
		}
		// _free();
	}
	return (EXIT_SUCCESS);
}
