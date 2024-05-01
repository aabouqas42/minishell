/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/01 11:54:57 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (data->args == 0 || *data->args == NULL)
		return (0);
	return (1);
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
		if (is_fod(cmd) == -1)
			return (do_error(NSFODIR_ERR, cmd), -1);
	}
	return (0);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	**paths;
	size_t	i;

	if (is_valid(cmd) == -1)
		return (0);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (data->program_path = _strdup(cmd), 1);
	paths = ft_split(env_grepvalue("PATH"), ':');
	if (paths == NULL)
		safe_exit(-1);
	i = 0;
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
	free_tab(paths);
	if (data->program_path == NULL)
		do_error(COMDNF_ERR, cmd);
	return (data->program_path != NULL);
}
