/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/29 10:52:55 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data	*data;

	data = data_hook(NULL);
	if (is_same(data->args[0], "exit"))
		safe_exit(0);
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
	ignore there_is_next;
	ignore args;
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
		set_in_out();
		execve(data->program_path, argv, env_to_2darray());
	}
	if (there_is_next)
	{
		close(data->fds[1]);
		data->oldfd && close(data->oldfd) && (data->oldfd = data->fds[0]);
	}
	printf("--[%d %d]--\n", data->oldfd, there_is_next);
}

int	read_input(t_data *data)
{
	data->usrinput = readline(data->prompt);
	if (data->usrinput == NULL || *data->usrinput == '\0')
	{
		free(data->usrinput);
		data->usrinput = NULL;
		return (0);
	}
	add_history(data->usrinput);
	return (1);
}

void	handle_input(t_data *data)
{
	int	i;
	
	split_usrin(data->usrinput);
	if (is_valid_input(data->args) == 0)
		return ;
	data->cmds = get_commands();
	if (data->cmds[1] == NULL && builtins())
		return;
	prt_tab(data->args);
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
	init_default_envs();
	while (1)
	{
		if (!read_input(&data) || !check_quotes_closed(data.usrinput))
			continue;
		handle_input(&data);
		while (waitpid(-1, &data.exit_status, 0) != -1);
		free_matrix(data.cmds);
		data.cmds = NULL;
		free (data.args);
		data.args = NULL;
		free (data.flags);
		data.flags = NULL;
		free (data.usrinput);
		data.usrinput = NULL;
	}
	return (EXIT_SUCCESS);
}
