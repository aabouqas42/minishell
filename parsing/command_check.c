/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:55:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/14 20:15:10 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_arguments(int ac, char **av)
{
	(void) av;
	if (ac != 1)
	{
		print(2, "minishell : too many arguments", 1);
		exit(1);
	}
}

void	prt_lst(t_arg *ptr)
{
	while (ptr)
	{
		printf("[%s{%d}]\n", ptr->value, ptr->type);
		t_arg	*ptr2 = ptr->list;
		while (ptr2)
		{
			printf("--->[%s]\n", ptr2->value);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	
}

int	expand_usrin(t_arg *args)
{
	char	*arg;
	char	qt;

	while (args)
	{
		arg = args->value;
		qt = 0;
		char	*exp = NULL;
		while (arg && *arg)
		{
			if ((*arg == DQT && qt != SQT) || (*arg == SQT && qt != DQT))
			{
				qt = (qt == 0) * (*arg);
				if (qt == 0)
				{
					if (t_arg_get_last(args->list))
					{
						t_arg_get_last(args->list)->value = _strjoin(t_arg_get_last(args->list)->value, exp);
						free(exp);
						exp = NULL;
					}
				}
			}
			else if (*arg == '$')
			{
				arg += set_var(arg +1, &exp);
				if (qt == 0)
				{
					split_expanded(exp, &args->list);
					free(exp);
				}
				else if (qt != SQT)
				{
					if (t_arg_get_last(args->list))
						t_arg_get_last(args->list)->value = ft_strjoin(t_arg_get_last(args->list)->value, exp);
					else
						t_arg_put(exp, ARG_WORD, &args->list);
				}
				exp = NULL;
			} else
				exp = _strnjoin(exp, arg, 1);
			arg += (*arg != '\0');
		}
		free(exp);
		if (args->list == NULL)
			args->value = exp_with_no_qts(args->value, 0);
		args = args->next;
	}
	return (1);
}

int	is_valid_input(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (check_qts(data->usrinput) == 0)
		return (0);
	if (split_usrin(data->usrinput) == 0)
		return (0);
	if (expand_usrin(data->args) == 0)
		return (0);
	prt_lst(data->args);
	// printf("%p\n", data->args->list);
	if (check_redirections(data->args) == 0)
		return (0);
	if (get_commands(data->args) == 0)
		return (0);
	// return(0);
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
