/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/08 12:59:41 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	prt_list(t_arg *arg)
{
	while (arg)
	{
		printf("[%s] ", arg->value);
		arg = arg->next;
	}
	printf("\n");
}

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

void	program_exec(t_cmd *cmd, int first, int next)
{
	t_data	*data;
	int		child_pid;
	(void )first;
	// (void )cmd;

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
		//get argv should run inside the child proc to open redi files inside child proc
		// the idea is initializing clean argv inside get_commands() and get open files here :)
		init_redirections(cmd);
		set_pipes(cmd, first, next);
		set_io(cmd);
		if (is_builtin(cmd))
		{
			run_builtin(cmd);
			exit(data->exit_status);
		}
		if (cmd->argv == NULL || is_valid_cmd(data, cmd->argv[0]) == 0)
			exit(127);
		init_env_array();
		execve(data->program_path, cmd->argv, data->env_2d);
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
	t_cmd	*cmds;
	int		next;

	if (is_valid_input() == 0)
		return ;
	cmds = data->cmds;
	if (cmds && cmds->next == NULL && is_builtin(cmds))
	{
		printf("built-in:%s\n", cmds->argv[0]);
		builtins(cmds);
		return ;
	}
	data->oldfd = 0;
	while (cmds)
	{
		next = cmds->next != NULL;
		program_exec(cmds, cmds == data->cmds, next);
		cmds = cmds->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
	{
		print(2, "minishell : too many arguments", 1);
		return (1 + ((size_t)av * 0));
	}
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
