/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/16 17:55:19 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	buildins(t_data *data)
{
	if (!ft_strncmp(data->argv[0], "exit", 4) && ft_strlen(data->argv[0]) == 4)
		return (_free(data), exit(0), 1);
	if (!ft_strncmp(data->argv[0], "clear", 5) && ft_strlen(data->argv[0]) == 5)
		return (printf("\e[1;1H\e[2J"), 1);
	if (!ft_strncmp(data->argv[0], "cd", 2) && ft_strlen(data->argv[0]) == 2)
		return (cd(data->argv[1]), 1);
	if (!ft_strncmp(data->argv[0], "echo", 4) && ft_strlen(data->argv[0]) == 4)
		return (echo(data->line + ft_strlen(data->argv[0])), 1);
	if (!ft_strncmp(data->argv[0], "pwd", 3) && ft_strlen(data->argv[0]) == 3)
		return (pwd(), 1);
	return (0);
}

int	execute(t_data *data)
{
	int	child_pid;

	data->line = readline(data->promte);
	if (data->line == NULL || *data->line == '\0')
		return (0);
	add_history(data->line);
	data->argv = _split(data->line, ' ');
	if (buildins(data))
		return (0);
	if (is_valid_cmd(data, data->argv[0]) != 1)
	{
		printf("\033[31mCommand not found : %s\033[0m\n", data->line);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		execve(data->program_path, data->argv, data->env);
	return (-1);
}

void	f()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	// goto here;
	data_init(&data, env);
	int i = 0;
	while (1)
	{
		execute(&data);
		waitpid(-1, NULL, 0);
		free (data.program_path);
		free (data.line);
		free_tab(data.argv);
		data.program_path = NULL;
	}
	// char **argv;
	// here:
	// 	argv = _split("echo -n \"   hello world   \" --static    ", ' ');
	// 	i = 0;
	// 	while (argv[i])
	// 		printf("%s\n", argv[i++]);
	return (EXIT_SUCCESS);
}

// int main()
// {
// 	t_env *head;

// 	head = NULL;

// 	env_add("key", "value", &head);
// 	env_add("key1", "value2", &head);
// 	env_add("key2", "value3", &head);
// 	env_print(head);
// }