/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/30 19:23:56 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	saver(char tosave)
{
	static char saved;
	char 		tmp;

	tmp = saved;
	if (tosave == 0)
		return (saved = 0, tmp);
	saved = tosave;
	return (0);
}

t_flags	*init_flags(char **usrin)
{
	t_flags	*flags;
	int		i;
	int		size;

	size = 0;
	while (usrin[size])
		size++;
	flags = malloc (size * sizeof(t_flags));
	if (flags == NULL)
		safe_exit(-1);
	ft_bzero(flags, size * sizeof(t_flags));
	i = 0;
	while (usrin[i])
	{
		if (is_io_op(usrin[i]))
			flags[i] = FLAG_IO_OP;
		i++;
	}
	return (flags);
}

int	is_valid_input(char **usrin)
{
	t_data	*data;

	if (usrin == NULL)
		return (0);
	data = data_hook(NULL);
	data->flags = init_flags(usrin);
	if (check_redirections(data->args) == 0)
		return (0);
	expand_input(data->args);
	// prt_tab(data->args);
	if (data->args == 0 || *data->args == NULL)
		return (0);
	return (1);
}

void	get_program_path(char *cmd)
{
	char	*program_path;

	program_path = _strdup(cmd);
	if (program_path == NULL)
		safe_exit(-1);
	data_hook(NULL)->program_path = program_path;
}

int	is_fod(char *name)
{
	struct stat	st;

	if (name == NULL)
		return (-1);
	if (stat(name, &st) == 0)
	{
		if (S_ISREG(st.st_mode))
			return (1);
		if (S_ISDIR(st.st_mode))
			return (2);
		return (0);
	}
	return (-1);
}

int	is_valid(char *cmd)
{
	if (cmd == NULL)
		return (do_error(COMDNF_ERR, cmd), 0);
	if (_strlenc(cmd, 0) == 0)
		return (do_error(COMDNF_ERR, cmd), -1);
	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.'))
	{
		if (is_fod(cmd) == FILE && access(cmd, X_OK) == -1)
			return (do_error(PERMIDEN_ERR, cmd), -1);
		if (is_fod(cmd) == DIRE)
			return (do_error(ISDIR_ERR, cmd), -1);
		// must check it 1 because /bin/ls not work
		if (is_fod(cmd) == -1)
			return (do_error(NSFODIR_ERR, cmd), -1);
	}
	return (0);
}

// int	is_dir(char *name)
// {
// 	DIR	*dir;

// 	dir = opendir(name);
// 	if (dir == NULL)
// 		return (0);
// 	closedir(dir);
// 	return (1);
// }

// int	is_valid_cmd(t_data *data, char *cmd)
// {
// 	char	*tmp;
// 	char	*paths;
// 	char	*program_path;
// 	size_t	i;

// 	if (access(cmd, X_OK) == 0)
// 		return (get_program_path(cmd), 1);
// 	if (is_valid(cmd) == -1)
// 		return (0);
// 	tmp = ft_strjoin("/", cmd);
// 	if (tmp == NULL)
// 		safe_exit(-1);
// 	paths = env_grepvalue("PATH");
// 	while (paths && *paths)
// 	{
// 		i = _strlenc(paths, ':');
// 		saver(paths[i]);
// 		paths[i] = '\0';
// 		program_path = ft_strjoin(paths, tmp);
// 		paths[i] = saver(0);
// 		if (program_path == NULL)
// 			(free(tmp), safe_exit(-1));
// 		if (access(program_path, X_OK) == 0)
// 			return (data->program_path = program_path, free(tmp), 1);
// 		free(program_path);
// 		paths += i + (paths[i] == ':');
// 	}
// 	return (free(tmp), do_error(COMDNF_ERR, cmd), 0);
// }

int	is_valid_cmd(t_data *data, char *cmd)
{
	char			**paths;
	static size_t	i;

	if (is_valid(cmd) == -1)
		return (0);
	/**
	 * must check if the cmd is valid first because "/"
	 * is a dir and access returns 0 so it will execve
	 * will failde and create a new procces :)
	 */
	if (access(cmd, X_OK) == 0)
		return (get_program_path(cmd), 1);
	paths = ft_split(env_grepvalue("PATH"), ':');
	while (paths && paths[i])
	{
		paths[i] = _strjoin(paths[i], "/");
		data->program_path = ft_strjoin(paths[i], cmd);
		if (access(data->program_path, X_OK) == 0)
			break ;
		free (data->program_path);
		data->program_path = NULL;
		i++;
	}
	if (data->program_path == NULL)
		do_error(COMDNF_ERR, cmd);
	return (free_tab(paths), i = 0, data->program_path != NULL);
}
