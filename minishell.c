/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/19 10:37:32 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins()
{
	t_data *data;

	data = data_hook(NULL);
	if (!_strcmp(data->commands[0], "exit"))
		safe_exit(0);
	if (!_strcmp(data->commands[0], "cd"))
		return (cd(data), 1);
	if (!_strcmp(data->commands[0], "echo"))
		return (echo(), 1);
	if (!_strcmp(data->commands[0], "pwd"))
		return (pwd(), 1);
	if (!_strcmp(data->commands[0], "env"))
		return (env_print(data->env), 1);
	if (!_strcmp(data->commands[0], "export"))
		return (_export(), 1);
	return (0);
}

int	cmd_err()
{
	char	**commands;
	size_t	i;

	
	commands = data_hook(NULL)->commands;
	i = 0;
	while (commands[i])
	{
		if (arg_is_io_operator(commands[i]))
		{
			if ((i == 0 && arg_is_io_operator(commands[i]))
				|| (arg_is_io_operator(commands[i -1]) || arg_is_io_operator(commands[i +1])))
				// || commands[i +1] == NULL || arg_is_io_operator(commands[i +1]))
				return (printf("syntaxxx errrrr\n"), 1);
		}
		// if (commands[i][0] == '|' && (commands[i -1]|| commands[i +1] == NULL))
		// if ((commands[i][0] == '>' || commands[i][0] == '<' ) && (commands[i -1] == NULL || commands[i +1] == NULL))
		// 	return (printf("syntaxxx errrrr\n"), 1);
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
		if (_strcmp(cmds[i], "|") == 0)
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
	cmds = p_calloc((cmds_counter(commands) + 1) * sizeof(char **));
	i = 0;
	while (commands && *commands)
	{
		if (_strcmp(*commands, "|") != 0)
		{
			cmds[i] = _realloc(cmds[i], *commands);
		}else
			i++;
		commands++;
	}
	return (cmds);
}

void	run_cmd(char	**argv_tmp)
{
	char	**argv;
	int		child_pid;
	int		action;
	int		in;
	int		out;

	in = 0;
	out = 1;
	argv = NULL;
	child_pid = fork();
	if (child_pid == 0)
	{
		while (*argv_tmp)
		{
			if (_strcmp(*argv_tmp, ">") == 0 || _strcmp(*argv_tmp, ">>") == 0)
			{
				action = O_RDWR | O_CREAT | (!_strcmp(*argv_tmp, ">") * O_TRUNC) + (!_strcmp(*argv_tmp, ">>") * O_APPEND);
				argv_tmp++;
				if (out > 1)
					close(out);
				out = open(*argv_tmp, action, 0666);
				if (out == -1)
					perror("open");
				printf("<F%s> (%d)", *argv_tmp, out);
			}else if (_strcmp(*argv_tmp, "<") == 0)
			{
				
				argv_tmp++;
				in = open(*argv_tmp, O_RDONLY);
			}else
				argv = _realloc(argv, *argv_tmp);
			argv_tmp++;
		}
		
	}
}

int	execute()
{
	t_data	*data;
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
	while (cmds && *cmds)
	{
		run_cmd(*cmds);
		cmds++;
	}
	// waitpid(-1, NULL, 0);
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
	t_data		*data;
	char		*value;

	data = data_hook(NULL);
	ft_bzero(data, sizeof(t_data));
	data->prompt = get_prompt();
	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=');
		*(value) = '\0';
		if (_strcmp(*base_env, "SHLVL") == 0)
		{
			value = ft_itoa(ft_atoi(value +1) + 1);
			if (value == NULL)
				safe_exit(-1);
			env_export(*base_env, value);
		}else
			env_export(*base_env, value +1);
		*(value) = '=';
		base_env++;
	}
	if (env_grepvalue("PATH") == 0)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == 0)
		env_export("SHLVL", "1");
}

// void ex()
// {
// 	system("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	printf("\e[1;1H\e[2J");
	data_hook(&data);
	data_init(env);
	while (1)
	{
		execute();
		waitpid(-1, &data.exit_status, 0);
		free (data.program_path);
		free (data.usrinput);
		free_tab(data.commands);
		data.commands = NULL;
		data.program_path = NULL;
	}
	return (EXIT_SUCCESS);
}
