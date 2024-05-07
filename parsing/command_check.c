/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/07 19:45:56 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_input(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (check_qts(data->usrinput) == 0)
		return (0);
	split_usrin(data->usrinput);
	expand_input(data->args);
	// prt_list (data->args);
	if (check_redirections(data->args) == 0)
		return 0;
	get_commands(data->args);
	// while (data->cmds)
	// {
	// 	printf("in : %d, out : %d, cmd : %s\n", data->cmds->in, data->cmds->out, data->cmds->linked_argv->value);
	// 	if (data->cmds->in != 0)
	// 		close(data->cmds->in);
	// 	data->cmds = data->cmds->next;
	// }
	return 1;
	// no syntax error :)
	// free 
	// while (data->_args)
	// {
	// 	printf("--[%s]--\n", data->_args->value);
	// 	data->_args = data->_args->next;
	// }
	// get_commands(data->_args);
	// while (data->cmds)
	// {
		// printf("HEREDOCS OF : %s\n", data->cmds->_argv->value);
		// int j = 0;
		// while (data->cmds->heredocs && data->cmds->heredocs[j])
		// {
		// 	printf("[%s]", data->cmds->heredocs[j]);
		// 	j++;
		// }
		// printf("\n");
	// 	data->cmds = data->cmds->next;
	// }
	// init_heredocs(data->cmds);
	// for (int i = 0; data->cmds[i].argv; i++)
	// {
	// 	data->cmds[i].out = 1;
	// 	for (int j = 0;data->cmds[i].argv[j]; j++)
	// 	{
	// 		printf("[%s %d] ", data->cmds[i].argv[j], data->cmds[i].flags[j].is_io_op);
	// 	}
	// 	printf("in : %d , out : %d", data->cmds[i].in, data->cmds[i].out);
	// 	printf("\n");
	// }
	// data->syn_err = 0;
	// return (0);
	// if (data->usrinput == NULL)
	// 	return (0);
	// if (check_redirections(data->args) == 0)
	// 	return (0);
	// expand_input(data->args);
	// if (data->args == 0 || *data->args == NULL)
	// 	return (0);
	// get_commands(data->_args);
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
	if (_strlen(cmd) == 0)
		return (do_error(COMDNF_ERR, cmd), 0);
	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.'))
	{
		if (is_fod(cmd) == _FILE && access(cmd, X_OK) == 0)
			return (do_error(PERMIDEN_ERR, cmd), 0);
		if (is_fod(cmd) == _DIRE)
			return (do_error(ISDIR_ERR, cmd), 0);
		if (is_fod(cmd) == 0)
			return (do_error(NSFODIR_ERR, cmd), 0);
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
