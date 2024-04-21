/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:43:03 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/21 17:26:42 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_defaults()
{
	t_data	*data;

	data = data_hook(NULL);
	if (data == NULL)
		return ;
	if (env_grepvalue("PATH") == 0)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == 0)
		env_export("SHLVL", "1");
}

void	data_init(char **base_env)
{
	t_data	*data;
	char	*value;
	char	*number;

	data = data_hook(NULL);
	ft_bzero(data, sizeof(t_data));
	data->out = 1;
	data->prompt = get_prompt();
	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=');
		*(value) = '\0';
		if (is_same(*base_env, "SHLVL"))
		{
			number = ft_itoa(ft_atoi(value + 1) + 1);
			if (number == NULL)
				safe_exit(-1);
			env_export(*base_env, number);
			free (number);
		} else
			env_export(*base_env, value +1);
		*(value) = '=';
		base_env++;
	}
}
