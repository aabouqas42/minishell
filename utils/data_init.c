/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:43:03 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/08 12:38:39 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_default_envs(void)
{
	if (env_grepvalue("PATH") == NULL)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == NULL)
		env_export("SHLVL", "1");
	if (env_grepvalue("PWD") == NULL)
		env_export("PWD", get_curr_path());
}

void	export_base_envs(char **base_env)
{
	char	*value;
	char	*number;

	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=');
		*(value) = '\0';
		if (is_same(*base_env, "SHLVL"))
		{
			if (ft_atoi(value +1) == 999)
				env_export(*base_env, "");
			else
			{
				number = ft_itoa(ft_atoi(value +1) + 1);
				if (number == NULL)
					safe_exit(-1);
				env_export(*base_env, number);
				free (number);
			}
		}
		else
			env_export(*base_env, value +1);
		*(value) = '=';
		base_env++;
	}
}

void	data_init(char **base_env)
{
	t_data	*data;

	data = data_hook(NULL);
	tcgetattr(0, data->old_termios);
	ft_bzero(data, sizeof(t_data));
	data->prompt = get_prompt();
	export_base_envs(base_env);
	export_default_envs();
}
