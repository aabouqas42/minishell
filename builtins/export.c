/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/07 18:34:18 by mait-elk         ###   ########.fr       */
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

int	_export(char **argv)
{
	t_data	*data;
	size_t	i;

	data = data_hook(NULL);
	if (data == NULL || argv == NULL)
		return (0);
	if (argv[1] == NULL || is_io_op(argv[1]))
		return (env_sort(data->env), 1);
	i = 1;
	while (argv[i])
	{
		set_value(argv[i]);
		i++;
	}
	return (0);
}
