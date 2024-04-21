/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/21 17:37:23 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// char	*path_prog(char *cmd)
// {
// 	char	*program;
// 	char	*paths;
// 	char	*path;

// 	program = NULL;
// 	path = NULL;
// 	paths = env_get("PATH", data_hook(NULL));
// 	while (*paths)
// 	{
		
// 		paths++;
// 	}
// }

int	builtins()
{
	t_data *data;

	data = data_hook(NULL);
	if (is_same(data->commands[0], "exit"))
		safe_exit(0);
	if (is_same(data->commands[0], "cd"))
		return (cd(data), 1);
	if (is_same(data->commands[0], "echo"))
		return (echo(), 1);
	if (is_same(data->commands[0], "pwd"))
		return (pwd(), 1);
	if (is_same(data->commands[0], "env"))
		return (env_print(data->env), 1);
	if (is_same(data->commands[0], "export"))
		return (_export(), 1);
	return (0);
}

int	check_input()
{
	char	**cmds;
	int		i;

	cmds = data_hook(NULL)->commands;
	i = 0;
	while (cmds[i])
	{
		if ((i == 0 && is_io_op(cmds[i]))
			|| (is_io_op(cmds[i]) && cmds[i + 1] == NULL)
			|| (is_same(cmds[i], "|")
			&& is_same(cmds[i + 1], "|"))
			|| (is_same(cmds[i], "&&")
			|| is_same(cmds[i], "(")
			|| is_same(cmds[i], ")")
			|| is_same(cmds[i], "()")
			|| is_same(cmds[i], "&"))
			)
		{
			ft_putstr_fd("Syntax Error\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	run_cmd(char **argv_tmp, int next_pipe, int isfirst)
{
	t_data	*data;
	char	**argv;
	int		child_pid;
	int		action;

	data = data_hook(NULL);
	argv = NULL;
	child_pid = fork();
	if (child_pid == 0)
	{
		while (*argv_tmp)
		{
			if (is_same(*argv_tmp, ">") || is_same(*argv_tmp, ">>"))
			{
				action = O_RDWR | O_CREAT | (is_same(*argv_tmp, ">") * O_TRUNC) + (is_same(*argv_tmp, ">>") * O_APPEND);
				argv_tmp++;
				data->out > 1 && close(data->out);
				data->out = open(*argv_tmp, action, 0666);
				if (data->out == -1)
					perror("open");
			}else if (is_same(*argv_tmp, "<<"))
			{
				argv_tmp++;
				data->in = open(*argv_tmp, O_RDONLY);
			} else
				argv = _realloc(argv, *argv_tmp);
			argv_tmp++;
		}
		if (isfirst && next_pipe)
			dup2(data->fds[1], 1);
		if (!isfirst && next_pipe)
		{
			dup2(data->oldfd, 0);
			dup2(data->fds[1], 1);
		}
		if (!isfirst && !next_pipe)
			dup2(data->oldfd, 0);
		close (data->fds[0]);
		close (data->fds[1]);
		close(data->oldfd);
		//
		// if (data->out != 1)
		// {
		// 	dup2(data->out, STDOUT_FILENO);
		// 	close (data->out);
		// }
		// if (data->in != 0)
		// {
		// 	dup2(data->in, STDIN_FILENO);
		// 	close (data->in);
		// }
		execve(data_hook(NULL)->program_path, argv, env_to_2darray());
	}
	free(data->program_path);
}

int	request_input()
{
	t_data	*data;
	int		i;

	data = data_hook(NULL);
	data->usrinput = readline(data->prompt);
	if (data->usrinput == NULL || *data->usrinput == '\0')
		return (0);
	add_history(data->usrinput);
	if (args_is_valid(data->usrinput) == 0)
		return (do_error(SYNTAX_ERR), 0);
	data->commands = _split(data->usrinput);
	data->cmds = get_commands();
	i = 0;
	while (data->cmds && data->cmds[i])
	{
		if (!is_valid_cmd(data, data->cmds[i][0]))
			return (do_error(COMDNF_ERR), 0);
		pipe(data->fds);
		run_cmd(data->cmds[i], data->cmds[i + 1] != NULL, i == 0);
		close(data->fds[1]);
		data->oldfd && close(data->oldfd);
		data->oldfd = data->fds[0];
		i++;
	}
	return (close(data->oldfd), data->oldfd = 0, -1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	data_hook(&data);
	data_init(env);
	set_defaults();
	while (1)
	{
		request_input();
		while (waitpid(-1, &data.exit_status, 0) != -1);
		free_matrix(data.cmds);
		free (data.usrinput);
		free (data.commands);
	}
	return (EXIT_SUCCESS);
}
