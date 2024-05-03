/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:31:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/03 15:31:47 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"



// void print_open_file_descriptors(char *c)
// {
//    int fd;
//     char path[256];
    
//     for(fd = 0; fd < 2500; fd++) {
//         if (fcntl(fd, F_GETFD) != -1) {
//             if (fcntl(fd, F_GETPATH, path) != -1) {
//                 dprintf(2, "%s :: File descriptor %d is referencing: %s\n", c, fd, path);
//             } else {
//                 dprintf(2, "%s :: File descriptor %d is not associated with an open file.\n", c, fd);
//             }
//         }
//     }
// }

void	close_unused_fds(int there_is_next)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->fds[1])
		close(data->fds[1]);
	if (data->oldfd)
		close(data->oldfd);
	if (there_is_next)
		data->oldfd = data->fds[0];
	else if (data->fds[0])
		close(data->fds[0]);
}

void	program_runner(char **args, int first, int there_is_next)
{
	t_data	*data;
	char	**argv; 
	int		child_pid;

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
		// prt_tab(argv);
		if (argv == NULL || is_valid_cmd(data, argv[0]) == 0)
			exit(-1);
		set_pipes(first, there_is_next);
		set_io();
		execve(data->program_path, argv, get_env_array());
		exit(-1);
	}
	close_unused_fds(there_is_next);
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

	// for (int i = 0;data->cmds[i]; i++)
	// {
	// 	for (int j = 0;data->cmds[i][j]; j++)
	// 	{
	// 		printf("%s ", data->cmds[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// for (int i = 0;data->cmds[i]; i++)
	// {
	// 	for (int j = 0;data->cmds[i][j]; j++)
	// 	{
	// 		printf("%s ", data->cmds[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// return ;
	if (is_valid_input(data->args) == 0)
	{
		free_tab(data->args);
		data->args = NULL;
		return ;
	}
	data->cmds = get_commands();
	// if (data->cmds[1] == NULL && builtins())
	// 	return ;
	i = 0;
	data->oldfd = 0;
	int	j = 0;
	t_flags *p = data->flags;
	while (data->cmds && data->cmds[i])
	{
		program_runner(data->cmds[i], i == 0, data->cmds[i + 1] != NULL);
		j = 0;
		while (data->cmds[i][j])
		{
			j++;
			data->flags++;
		}
		data->flags++;
		i++;
	}
	data->flags = p;
}


int	main(int ac, char **av, char **env)
{
	t_data	data;
	ignore	ac;
	ignore	av;

	data_hook(&data);
	data_init(env);
	// signal(SIGQUIT, signal_handler);
	// signal(SIGQUIT, signal_handler);
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
