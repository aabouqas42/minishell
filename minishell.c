/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/01 20:11:11 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data	*data;
	char	**args;
	int		ret;
	int		savein;
	int		saveout;

	ret = 0;
	data = data_hook(NULL);
	args = get_argv(data->args);
	data->args = args;
	savein = dup(0);
	saveout = dup(1);
	if (data->in != 0)
	{
		dup2(data->in, 0);
		close(data->in);
	}
	if (data->out != 1)
	{
		dup2(data->out, 1);
		close(data->out);
	}
	// printf("in : %d, out : %d\n", data->in, data->out);
	if (is_same(data->args[0], "exit"))
		(printf("exit\n"), safe_exit(0));
	if (is_same(data->args[0], "cd"))
		ret = (cd(data), 1);
	if (is_same(data->args[0], "echo"))
		ret = (echo(), 1);
	if (is_same(data->args[0], "pwd"))
		ret = (pwd(), 1);
	if (is_same(data->args[0], "env"))
		ret = (env_print(data->env), 1);
	if (is_same(data->args[0], "export"))
		ret = (_export(), 1);
	if (is_same(data->args[0], "unset"))
		ret = (env_unset(data->args[1], &data->env), 1);
	if (data->in != 0)
	{
		dup2(savein, 0);
		close(savein);
	}
	if (data->out != 1)
	{
		dup2(saveout, 1);
		close(saveout);
	}
	// P("%d\n", ret);
	return (ret);
}

void	program_runner(char **args, int first, int there_is_next)
{
	t_data	*data;
	char	**argv; 
	int		child_pid;

	ignore first;
	data = data_hook(NULL);
	there_is_next && pipe(data->fds);
	child_pid = fork();
	if (child_pid == -1)
	{
		ft_putstr_fd("Unexpected Error\n", 2);
		return ;
	} else if (child_pid == 0)
	{
		argv = get_argv(args);
		// if (data->in > 0)
		// 	close(data->fds[0]);
		// if (data->out > 1)
		// 	close(data->fds[1]);
		set_pipes(first, there_is_next);
		if (is_valid_cmd(data, argv[0]) == 0)
		{
			// printf("---[%d]--%d-\n", data->oldfd, data->fds[1]);
			// close (data->oldfd);
			// close (data->fds[1]);
			// close (data->fds[0]);
			exit(-1);
		}
		printf("cmd : %s, in : %d, out : %d , oldfd: %d\n", data->program_path, data->in, data->out, data->oldfd);
		set_io();
		execve(data->program_path, argv, get_env_array());
		exit(-1);
	}
	//THERE ERROR IN TEST cat | cat | askdakdsk
	data->fds[1] && close(data->fds[1]);
	data->oldfd && close(data->oldfd);
	if (there_is_next)
		data->oldfd = data->fds[0];
	else
		data->fds[0] && close(data->fds[0]);
}

int	read_input(t_data *data)
{
	data->usrinput = readline(data->prompt);
	if (data->usrinput && *data->usrinput)
		add_history(data->usrinput);
	if (data->usrinput == NULL)
		safe_exit(-1);
	if (*data->usrinput == '\0' || check_qts(data->usrinput) == 0)
	{
		free(data->usrinput);
		data->usrinput = NULL;
		return (-1);
	}
	return (1);
}

void	_free()
{
	t_data	*data;

	data = data_hook(NULL);
	free_matrix(data->cmds);
	data->cmds = NULL;
	free (data->args);
	data->args = NULL;
	free (data->flags);
	data->flags = NULL;
	free (data->usrinput);
	data->usrinput = NULL;
}

void	handle_input(t_data *data)
{
	int	i;
	split_usrin(data->usrinput);
	if (is_valid_input(data->args) == 0)
	{
		free_tab(data->args);
		data->args = NULL;
		return ;
	}
	data->cmds = get_commands();
	// if (data->cmds[1] == NULL && builtins())
	// 	return ;
	data->oldfd = 0;
	i = 0;
	while (data->cmds && data->cmds[i])
	{
		program_runner(data->cmds[i], i == 0, data->cmds[i + 1] != NULL);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	ignore	ac;
	ignore	av;

	data_hook(&data);
	data_init(env);
	while (1)
	{
		if (read_input(&data) != -1)
		{
			handle_input(&data);
			while (waitpid(-1, &data.exit_status, 0) != -1)
			{
				if (data.exit_status >> 8 == -1)
					safe_exit(-1);
			}
		}
		_free();
	}
	return (EXIT_SUCCESS);
}
