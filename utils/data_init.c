/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:43:03 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/29 10:31:35 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_default_envs()
{
	if (env_grepvalue("PATH") == NULL)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == NULL)
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
			if ((value + 1)[0] == '\0')
				number = "1";
			else if (ft_atoi(value + 1) > 999)
				number = "";
			else
			{
				number = ft_itoa(ft_atoi(value +1) + 1);
				if (number == NULL)
					safe_exit(-1);
			}
			env_export(*base_env, number);
			free (number);
		} else
			env_export(*base_env, value +1);
		*(value) = '=';
		base_env++;
	}
}
