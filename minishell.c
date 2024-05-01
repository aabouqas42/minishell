/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/01 09:44:09 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data	*data;

	data = data_hook(NULL);
	if (is_same(data->args[0], "exit"))
		(printf("exit\n"), safe_exit(0));
	if (is_same(data->args[0], "cd"))
		return (cd(data), 1);
	if (is_same(data->args[0], "echo"))
		return (echo(), 1);
	if (is_same(data->args[0], "pwd"))
		return (pwd(), 1);
	if (is_same(data->args[0], "env"))
		return (env_print(data->env), 1);
	if (is_same(data->args[0], "export"))
		return (_export(), 1);
	if (is_same(data->args[0], "unset"))
		return (env_unset(data->args[1], &data->env), 1);
	return (0);
}

int	check_input(char **cmds)
{
	int		i;

	i = 0;
	if (cmds && cmds[0][0] == '|')
		return (do_error(SYNTAX_ERR, cmds[0]), -1);
	while (cmds && cmds[i])
	{
		if (cmds[i][0] && ft_strchr("<>", cmds[i][0]))
		{
			if (cmds[i + 1] && ft_strchr("<>|", cmds[i + 1][0]))
				return (do_error(SYNTAX_ERR, cmds[i + 1]), -1);
			else if (cmds[i + 1] == NULL)
				return (do_error(SYNTAX_ERR, "newline"), -1);
		}
		if (cmds[i][0] && ft_strchr("|", cmds[i][0]))
		{
			if (cmds[i +1] && ft_strchr("|", cmds[i +1][0]))
				return (do_error(SYNTAX_ERR, cmds[i + 1]), -1);
			else if (cmds[i +1] == NULL)
				return (do_error(SYNTAX_ERR, "newline"), -1);
		}
		i++;
	}
	return (0);
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
		if (is_valid_cmd(data, argv[0]) == 0)
			exit(-1);
		set_pipes(first, there_is_next);
		set_io();
		execve(data->program_path, argv, get_env_array());
		// an other error here :) if execve fails you should exit :))))
		exit(-1);
	}
	if (there_is_next)
	{
		(data->fds[1] != 1) && close(data->fds[1]);
		data->oldfd && close(data->oldfd);
		data->oldfd = data->fds[0];
	}
}

int	read_input(t_data *data)
{
	char	*uin;

	data->usrinput = readline(data->prompt);
	uin = data->usrinput;
	if (uin && *uin)
		add_history(data->usrinput);
	if (uin == NULL || *uin == '\0' || check_qts(uin) == 0)
	{
		free(data->usrinput);
		data->usrinput = NULL;
		return (-1);
	}
	return (1);
}
void	_free();
void	handle_input(t_data *data)
{
	int	i;
	split_usrin(data->usrinput);
	if (is_valid_input(data->args) == 0)
	{
		// memory problem fixed here :)
		free_tab(data->args);
		data->args = NULL;
		_free();
		return ;
	}
	data->cmds = get_commands();
	if (data->cmds[1] == NULL && builtins())
		return ;
	data->oldfd = 0;
	i = 0;
	while (data->cmds && data->cmds[i])
	{
		program_runner(data->cmds[i], i == 0, data->cmds[i + 1] != NULL);
		i++;
	}
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

int	main(int ac, char **av, char **env)
{
	t_data	data;
	ignore	ac;
	ignore	av;

	data_hook(&data);
	data_init(env);
	while (1)
	{
		if (read_input(&data) == -1)
			continue ;
		handle_input(&data);
		while (waitpid(-1, &data.exit_status, 0) != -1);
		_free();
	}
	return (EXIT_SUCCESS);
}
