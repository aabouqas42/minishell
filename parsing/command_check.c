/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/17 11:41:33 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_arguments(int ac, char **av)
{
	(void) av;
	if (!isatty(0))
	{
		print(2, "minishell: TTY Required :)", 1);
		exit(1);
	}
	if (ac != 1)
	{
		print(2, "minishell : too many arguments", 1);
		exit(1);
	}
}

int	is_valid_input(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (check_qts(data->usrinput) == 0)
		return (0);
	if (split_usrin(data->usrinput) == 0)
		return (0);
	if (check_redirections(data->args) == 0)
		return (0);
	if (get_commands(data->args) == 0)
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
	if (env_grepvalue("PATH") == NULL && is_fod(cmd) == _DIRE)
		return (do_error(ISDIR_ERR, "", cmd), 0);
	if (_strlen(cmd) == 0)
		return (do_error(COMDNF_ERR, "", cmd), 0);
	if (ft_strchr(cmd, '/'))
	{
		if (is_fod(cmd) == _FILE && access(cmd, X_OK) != 0)
			return (do_error(PERMIDEN_ERR, "", cmd), 0);
		if (is_fod(cmd) == _DIRE)
			return (do_error(ISDIR_ERR, "", cmd), 0);
		if (is_fod(cmd) == -1)
		{
			print(2, "minishell: ", 0);
			print(2, cmd, 0);
			print(2, ": No such file or directory", 1);
			data_hook(NULL)->exit_status = 127 << 8;
			return (0);
		}
	}
	return (1);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	**paths;
	size_t	i;

	if (!is_valid(cmd))
		return (0);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (data->program_path = _strdup(cmd), 1);
	paths = ft_split(env_grepvalue("PATH"), ':');
	i = 0;
	while (paths && paths[i])
	{
		paths[i] = _strjoin(paths[i], "/");
		data->program_path = _strjoin(paths[i], cmd);
		if (access(data->program_path, X_OK) == 0
			&& is_fod(data->program_path) == _FILE)
			break ;
		free (data->program_path);
		data->program_path = NULL;
		i++;
	}
	if (data->program_path == NULL)
		do_error(COMDNF_ERR, "", cmd);
	return (data->program_path != NULL);
}
