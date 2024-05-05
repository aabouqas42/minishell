/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:38:17 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/05 09:04:51 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_builtin(t_data *data, char **args)
{
	if (data->out != 1 && dup2(data->out, 1))
		close(data->out);
	if (args == NULL)
		return (0);
	if (is_same(args[0], "exit"))
		(print(1, "exit", 1), safe_exit(0));
	if (is_same(args[0], "cd"))
		return (cd(data), 1);
	if (is_same(args[0], "echo"))
		return (echo(), 1);
	if (is_same(args[0], "pwd"))
		return (pwd(), 1);
	if (is_same(args[0], "env"))
		return (env_print(data->env), 1);
	if (is_same(args[0], "export"))
		return (_export(), 1);
	if (is_same(args[0], "unset"))
		return (env_unset(data->args[1], &data->env), 1);
	return (0);
}

static int	built_in_cmd(char *cmd)
{
	return (is_same(cmd, "exit")
		|| is_same(cmd, "cd")
		|| is_same(cmd, "echo")
		|| is_same(cmd, "pwd")
		|| is_same(cmd, "env")
		|| is_same(cmd, "export")
		|| is_same(cmd, "unset"));
}

int	builtins(void)
{
	t_data	*data;
	char	**args;
	int		ret;
	int		in;
	int		out;

	data = data_hook(NULL);
	// if (!built_in_cmd(data->args[2]))
	// 	return (0);
	args = get_argv(data->args);
	in = dup(0);
	out = dup(1);
	if (data->in != 0 && dup2(data->in, 0))
		close(data->in);
	if (data->out != 1 && dup2(data->out, 1))
		close(data->out);
	ret = run_builtin(data, args);
	dup2(in, 0);
	dup2(out, 1);
	close(out);
	close(in);
	data->in = 0;
	data->out = 1;
	return (free(args), ret);
}
