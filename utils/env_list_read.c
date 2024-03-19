/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:17:22 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/18 22:21:48 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int mini_api(t_env	*env_item, char *name)
{
	size_t	i;
	char	save_c;

	i = 0;
	while (*name)
	{
		while (name[i] && name[i] != '$')
			i++;
		save_c = name[i];
		name[i] = '\0';
		printf("<%s>", name);
		name[i] = save_c;
		// if (ft_strncmp(env_item->name, name, ft_strlen(name) +1) == 0)
		// {
		// 	printf("%s ", env_item->value);
		// 	return (1);
		// }
	}
	printf("%c", '\n');
	return (0);
}

void	env_prt_valueof(char *name, t_data	*data)
{
	t_env	*i;

	if (name && data && *name != '\0')
	{
		name++;
		i = data->_env;
		// if (*name == '?')
		// {
		// 	printf("%d", data->exit_status >> 8);
		// 	data->exit_status = 0;
		// 	return ;
		// }
		// while (i)
		// {
			if (mini_api(i, name));
				// break;
		// 	i = i->next;
		// }
	}
}
