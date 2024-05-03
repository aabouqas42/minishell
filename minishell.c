/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/03 16:37:19 by aabouqas         ###   ########.fr       */
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
		ft_putstr_fd("Unexpected Error\n", 2);
		return ;
	} else if (child_pid == 0)
	{
		argv = get_argv(args);
		if (argv == NULL || is_valid_cmd(data, argv[0]) == 0)
			exit(-1);
		set_pipes(first, next);
		set_io();
		execve(data->program_path, argv, get_env_array());
		exit(-1);
	}
	close_unused_fds(next);
}

int	read_input(t_data *data)
{
	data->usrinput = readline(data->prompt);
	if (data->usrinput == NULL)
		safe_exit(-1);
	if (*data->usrinput)
		add_history(data->usrinput);
	if (*data->usrinput == '\0' || check_qts(data->usrinput) == 0)
	{
		free(data->usrinput);
		data->usrinput = NULL;
		return (-1);
	}
	return (1);
}

int	get_argsc(char **args)
{
	int	argsc;

	argsc = 0;
	while (args && args[argsc])
		argsc++;
	return (argsc);
}

void	handle_input(t_data *data)
{
	int		index;
	int		next;
	int		first;
	t_flags	*ptr;

	if (is_valid_input() == 0)
	{
		free_tab(data->args);
		data->args = NULL;
		return ;
	}
	if (data->cmds[1] == NULL && builtins())
		return ;
	index = 0;
	data->oldfd = 0;
	ptr = data->flags;
	while (data->cmds && data->cmds[index])
	{
		first = index == 0;
		next = data->cmds[index + 1] != NULL;
		program_exec(data->cmds[index], first, next);
		data->flags += get_argsc(data->cmds[index]) + 1;
		index++;
	}
	data->flags = ptr;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	(void)	ac;
	(void)	av;

	data_hook(&data);
	data_init(env);
	while (1)
	{
		if (read_input(&data) != -1)
		{
			handle_input(&data);
			while (waitpid(-1, &data.exit_status, 0) != -1)
				if (data.exit_status >> 8 == -1)
					safe_exit(-1);
		}
		_free();
	}
	return (EXIT_SUCCESS);
}
