/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:34:25 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/05 20:17:20 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmds_counter(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds && cmds[i])
	{
		if (cmds[i] && ft_strncmp(cmds[i], "|", 3) == 0)
			j++;
		i++;
	}
	return (j + 1);
}

void	get_commands(t_arg *args)
{
	t_arg	*ptr;
	t_cmd	cmd;
	int		i;

	i = 0;
	ptr = args;
	// while (ptr)
	// {
	// 	printf("---[%s]---\n", ptr->value);
	// 	ptr = ptr->next;
	// }
	// printf("%s %d\n", args->value, args->type == ARG_PIPE);
	data_hook(NULL)->exit_status = 0;
	if (args->type > 1 && args->next == NULL)
		return (do_error(SYNTAX_ERR, "newline"));
	while (args)
	{
		cmd._argv = NULL;
		cmd.heredocs = NULL;
		while (args && args->type != ARG_PIPE)
		{
			if (args->type == ARG_HERDOC && args->next)
				cmd.heredocs = _realloc(cmd.heredocs, args->next->value);
			else
				t_arg_put(args->value, args->type, &cmd._argv);
			args = args->next;
		}
		t_cmd_add(cmd);
		// t_cmd	*c;
		// while (data_hook(NULL)->cmds)
		// {
		// 	int j = 0;
		// 	while (cmd.heredocs && cmd.heredocs[j])
		// 	{
		// 		printf("[%s]", cmd.heredocs[j]);
		// 		j++;
		// 	}
		// 	printf("\n");
		// 	data_hook(NULL)->cmds = data_hook(NULL)->cmds->next;
		// }
		if (args)
			args = args->next;
	}
}
