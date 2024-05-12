/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/12 17:16:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	program_exec(t_cmd *cmd, int first, int next)
{
	t_data	*data;
	int		child_pid;

	data = data_hook(NULL);
	if (next)
		pipe(data->fds);
	child_pid = fork();
	if (child_pid == -1)
		return ((void)print(2, "Unexpected Error", 1));
	if (child_pid == 0)
	{
		if (data->in)
			close(data->in);
		if (init_redirections(cmd) == 0)
			exit(1);
		(set_pipes(cmd, first, next), set_io(cmd));
		if (is_builtin(cmd))
			((void)run_builtin(cmd), exit(data->exit_status));
		if (cmd->argv == NULL || is_valid_cmd(data, cmd->argv[0]) == 0)
			exit(data->exit_status >> 8);
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
	{
		if (isatty(0))
		{
			printf("\x1b[1A%sexit\n", data->prompt);
			safe_exit(127);
		}
		safe_exit(0);
	}
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
		builtins(cmds);
		return ;
	}
	exit(0);
	data->oldfd = 0;
	while (cmds)
	{
		next = cmds->next != NULL;
		program_exec(cmds, cmds == data->cmds, next);
		cmds = cmds->next;
	}
}

void	restore(t_data *data)
{
	t_cmd	*cmds;

	cmds = data->cmds;
	while (cmds)
	{
		if (cmds->in != 0)
			close(cmds->in);
		cmds = cmds->next;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &data->old_term);
	dup2 (data->in, 0);
	close(data->in);
	_free();
}

void	lek()
{
	system("lsof -c minishell");
}

int	main(int ac, char **av, char **env)
{
	t_data		data;

	atexit(lek);
	check_arguments(ac, av);
	data_hook(&data);
	data_init(env);
	catch_signals();
	while (1)
	{
		data.in = dup(0);
		if (read_input(&data) != -1)
		{
			data.fix_doubleprt = 1;
			handle_input(&data);
			while (waitpid(-1, &data.exit_status, 0) != -1)
				if (data.exit_status >> 8 == -1)
					safe_exit(-1);
			data.fix_doubleprt = 0;
		}
		restore(&data);
	}
	return (EXIT_SUCCESS);
}
