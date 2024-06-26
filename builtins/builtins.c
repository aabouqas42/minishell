/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:38:17 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/12 18:01:20 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd != NULL && cmd->argv)
	{
		return (str_equal(cmd->argv[0], "exit")
			|| str_equal(cmd->argv[0], "cd")
			|| str_equal(cmd->argv[0], "echo")
			|| str_equal(cmd->argv[0], "pwd")
			|| str_equal(cmd->argv[0], "env")
			|| str_equal(cmd->argv[0], "export")
			|| str_equal(cmd->argv[0], "unset"));
	}
	return (0);
}

int	run_builtin(t_cmd *cmd)
{
	t_data	*data;

	data = data_hook(NULL);
	if (cmd->out != 1 && dup2(cmd->out, 1))
		close(cmd->out);
	if (cmd->argv == NULL)
		return (0);
	if (str_equal(cmd->argv[0], "exit"))
		__exit(cmd);
	if (str_equal(cmd->argv[0], "cd"))
		return (cd(cmd->argv), 1);
	if (str_equal(cmd->argv[0], "echo"))
		return (echo(cmd->argv), 1);
	if (str_equal(cmd->argv[0], "pwd"))
		return (pwd(), 1);
	if (str_equal(cmd->argv[0], "env"))
		return (env_print(data->env), 1);
	if (str_equal(cmd->argv[0], "export"))
		return (_export(cmd->argv), 1);
	if (str_equal(cmd->argv[0], "unset"))
		return (unset(cmd->argv + 1));
	return (0);
}

int	builtins(t_cmd *cmd)
{
	t_data	*data;
	int		ret;

	data = data_hook(NULL);
	if (init_redirections(cmd) == 0)
		return (0);
	if (cmd->in != 0 && dup2(cmd->in, 0))
		close(cmd->in);
	if (cmd->out != 1 && dup2(cmd->out, 1))
		close(cmd->out);
	ret = run_builtin(cmd);
	dup2(data->def_in, 0);
	dup2(data->def_out, 1);
	cmd->in = 0;
	cmd->out = 1;
	return (ret);
}
