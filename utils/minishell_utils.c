/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/10 09:33:19 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*data_hook(t_data *data)
{
	static t_data	*data_saved;

	if (data != NULL)
		data_saved = data;
	return (data_saved);
}

void	safe_exit(int status)
{
	t_data	*data;

	data = data_hook(NULL);
	free (data->usrinput);
	data->usrinput = NULL;
	free (data->program_path);
	data->program_path = NULL;
	clear_history();
	env_free_list(data->env);
	data->env = NULL;
	free (data->prompt);

	exit(status);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*user;

	user = getenv("USER");
	user = _strdup(user);
	if (user == NULL || *user == '\0')
		user = _strdup("unknown");
	if (user == NULL)
		safe_exit(-1);
	prompt = _strjoin(user, "@1337.ma $> ");
	return (prompt);
}

void	init_clear_argv(t_cmd *cmd)
{
	t_arg	*args;

	args = cmd->linked_argv;
	cmd->argv = NULL;
	while (args)
	{
		if (args->type == ARG_REDIN || args->type == ARG_REDOUT
			|| args->type == ARG_APPEND || args->type == ARG_HERDOC)
			args = args->next;
		else
			cmd->argv = _realloc(cmd->argv, args->value);
		args = args->next;
	}
}
