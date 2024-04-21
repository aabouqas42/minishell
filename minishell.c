/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/21 16:53:15 by mait-elk         ###   ########.fr       */
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
			|| is_same(cmds[i], "&")
			|| is_same(cmds[i], "{")
			|| is_same(cmds[i], "}")))
		{
			ft_putstr_fd("Syntax Error\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	cmds_counter(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds && cmds[i])
	{
		if (is_same(cmds[i], "|") == 0)
			j++;
		i++;
	}
	return (j + 1);
}

char	***get_commands()
{
	char	***cmds;
	char	**commands;
	int		i;

	commands = data_hook(NULL)->commands;
	cmds = _calloc((cmds_counter(commands) + 1) * sizeof(char **));
	i = 0;
	while (commands && *commands)
	{
		if (is_same(*commands, "|") == 0)
			cmds[i] = _realloc(cmds[i], *commands);
		else
			i++;
		commands++;
	}
	return (cmds);
}

void	run_cmd(char	**argv_tmp, int there_pipe, int is_first_cmd)
{
	char	**argv;
	int		child_pid;
	int		action;
	int		in;
	int		out;
	char	*heredoc = NULL;
	
	in =  0;
	out = 1;
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
				out > 1 && close(out);
				out = open(*argv_tmp, action, 0666);
				if (out == -1)
					perror("open");
			}else if (is_same(*argv_tmp, "<<"))
			{
				argv_tmp++;
				while (1)
				{
					char	*in = readline("heredoc> ");
					if (in && is_same(in, *argv_tmp))
						break;
					heredoc = ft_strjoin(heredoc, in);
					heredoc = ft_strjoin(heredoc, "\n");
				}
				printf("%s\n", heredoc);
			}
			else if (is_same(*argv_tmp, "<"))
			{
				
				argv_tmp++;
				in = open(*argv_tmp, O_RDONLY);
			} else
				argv = _realloc(argv, *argv_tmp);
			argv_tmp++;
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close (out);
		}
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close (in);
		}
		if (is_valid_cmd(data_hook(NULL), argv[0]) == 0)
		{
			ft_putstr_fd("minishell : command not Found\n", 2);
			return ;
		}
		else
			execve(data_hook(NULL)->program_path, argv, env_to_2darray());
	}
	(void)(there_pipe+is_first_cmd);
	waitpid(-1, NULL, 0);
	// free_tab(data_hook(NULL)->commands);
	// free(data_hook(NULL)->program_path);
}

int	request_input()
{
	t_data	*data;
	int		i;
	// int		child_pid;

	data = data_hook(NULL);
	data->usrinput = readline(data->prompt);
	if (data->usrinput == NULL || *data->usrinput == '\0')
		return (0);
	add_history(data->usrinput);
	if (args_is_valid(data->usrinput) == 0)
		return (do_error(SYNTAX_ERR), 0);
	data->commands = _split(data->usrinput);
	char ***cmds = get_commands();
	// int	fds[2];
	i = 0;
	while (cmds && cmds[i])
	{
		run_cmd(cmds[i], cmds[i +1] != NULL, i == 0);
		i++;
	}
	while(waitpid(-1, NULL, 0) != -1);
	// env_print(data->env);
	// if (data->commands == NULL || cmd_err())
	// 	return (1);
	// _redirection();
	// if (builtins())
	// 	return (0);
	// if (is_valid_cmd(data, data->commands[0]) != CMD_VALID)
	// {
	// 	printf("\e[31mminishell : %s command not found\e[0m\n", data->usrinput);
	// 	data->exit_status = 127 << 8;
	// 	return (-1);
	// }
	// child_pid = fork();
	// if (child_pid == 0)
	// 	execve(data->program_path, data->commands, env_to_2darray());
	return (-1);
}

void	data_init(char **base_env)
{
	t_data	*data;
	char	*value;
	char	*number;

	data = data_hook(NULL);
	ft_bzero(data, sizeof(t_data));
	data->prompt = get_prompt();
	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=');
		*(value) = '\0';
		if (is_same(*base_env, "SHLVL"))
		{
			number = ft_itoa(ft_atoi(value + 1) + 1);
			if (number == NULL)
				safe_exit(-1);
			env_export(*base_env, number);
			free (number);
		} else
			env_export(*base_env, value +1);
		*(value) = '=';
		base_env++;
	}
	if (env_grepvalue("PATH") == 0)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == 0)
		env_export("SHLVL", "1");
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	printf("\e[1;1H\e[2J");
	data_hook(&data);
	data_init(env);
	P("hello %d\n", 87867);
	while (1)
	{
		request_input();
		waitpid(-1, &data.exit_status, 0);
		// free (data.program_path);
		// free (data.usrinput);
		// free_tab(data.commands);
		data.commands = NULL;
		data.program_path = NULL;
	}
	return (EXIT_SUCCESS);
}
