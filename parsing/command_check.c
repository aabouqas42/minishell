/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/25 16:26:02 by aabouqas         ###   ########.fr       */
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

size_t	is_symbolee(char *str)
{
	if (!ft_strncmp("<<", str, 2) || !ft_strncmp(">>", str, 2))
	{
		saver(str[2]);
		str[2] = '\0';
		str[2] = saver(0);
		printf("[%s]", str);
		// *args_ptr = _realloc(*args_ptr, _strnjoin(NULL, str, 2));
		return (2);
	}
	if (str && *str && ft_strchr("<>|", *str) != NULL)
	{
		saver(str[1]);
		printf("[%s]", str);
		str[1] = saver(str[1]);
		// *args_ptr = _realloc(*args_ptr, _strnjoin(NULL, str, 1));
	}
	return (1);
}


// int	is_valid_input(char *usrin)
// {
// 	char	*res;
// 	char	qt;

// 	while (*usrin)
// 	{
// 		(1) && (usrin = skiper(usrin), res = NULL, qt = 0);
// 		while (*usrin && (!_spaces(*usrin) || qt))
// 		{
// 			if ((*usrin == '\"' && qt != '\'') || (*usrin == '\'' && qt != '\"'))
// 				qt = (qt == 0) * (*usrin);
// 			if (ft_strchr("<>|", *usrin) && !qt)
// 				break;
// 			(1) && (res = _strnjoin(res, usrin, 1), usrin++);
// 		}
// 		printf("[%s] ", res);
// 		usrin += is_symbolee(usrin);
// 	}
// 	printf("\n");
// 	return (0);
// }

void	get_program_path(char *cmd)
{
	char	*program_path;

	program_path = _strdup(cmd);
	if (program_path == NULL)
		safe_exit(-1);
	data_hook(NULL)->program_path = program_path;
}

int	is_dir(char *name)
{
	DIR	*dir;

	dir = opendir(name);
	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}

int	is_valid_cmd(t_data *data, char *cmd)
{
	char	*tmp;
	char	*paths;
	char	*program_path;
	char	c;
	size_t	i;

	if (cmd == NULL || is_dir(cmd))
		return (do_error(ISDIR_ERR, cmd), 0);
	if (_strlenc(cmd, 0) == 0)
		return (do_error(COMDNF_ERR, cmd), 0);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (get_program_path(cmd), 1);
		if (is_dir(cmd))
			return (do_error(ISDIR_ERR, cmd), 1);
		return (do_error(NSFODIR_ERR, cmd), 1);
	}
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		safe_exit(-1);
	paths = env_grepvalue("PATH");
	while (paths && *paths)
	{
		i = _strlenc(paths, ':');
		c = paths[i];
		paths[i] = '\0';
		program_path = ft_strjoin(paths, tmp);
		paths[i] = c;
		if (program_path == NULL)
			(free(tmp), safe_exit(-1));
		if (access(program_path, X_OK) == 0)
			return (data->program_path = program_path, free(tmp), 1);
		free(program_path);
		paths += i + (paths[i] == ':');
	}
	return (free(tmp), do_error(COMDNF_ERR, cmd), 0);
}
