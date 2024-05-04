/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/04 10:53:08 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_value(char *name)
{
	char	*save;
	char	*value;

	value = "";
	save = _strchr(name, '=');
	if (save == NULL || *name == '+' || *name == '=')
	{
		if (env_valid_name(name))
			env_export(name, NULL);
		else
			do_error(INVNAMEENV_ERR, name);
		return ;
	}
	if (*(save - 1) == '+')
	{
		*(save - 1) = '\0';
		value = env_grepvalue(name);
	}
	*save = '\0';
	value = ft_strjoin(value, save + 1);
	if (env_valid_name(name))
		env_export(name, value);
	else
		do_error(INVNAMEENV_ERR, name);
	free(value);
}

int	_export(void)
{
	t_data	*data;
	size_t	i;

	data = data_hook(NULL);
	if (data == NULL || data->args == NULL)
		return (0);
	if (data->args[1] == NULL || is_io_op(data->args[1]))
		return (env_sort(data->env), 1);
	i = 1;
	while (data->args[i])
	{
		set_value(data->args[i]);
		i++;
	}
	return (0);
}
