/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:43:03 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/12 14:58:02 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_default_envs(void)
{
	char	*curr_path;

	curr_path = get_curr_path(1);
	if (env_grepvalue("PATH") == NULL)
		env_export("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (env_grepvalue("SHLVL") == NULL)
		env_export("SHLVL", "1");
	if (curr_path != NULL)
	{
		env_export("PWD", curr_path);
		free (curr_path);
	}
}

void	export_base_envs(char **base_env)
{
	char	*value;
	char	*number;

	while (base_env && *base_env)
	{
		value = ft_strchr(*base_env, '=');
		*(value) = '\0';
		if (str_equal(*base_env, "SHLVL"))
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
	t_data		*data;
	extern int	rl_catch_signals;

	data = data_hook(NULL);
	ft_bzero(data, sizeof(t_data));
	data->prompt = get_prompt();
	export_base_envs(base_env);
	export_default_envs();
	data->pwd = _strdup(env_grepvalue("PWD"));
	tcgetattr(STDIN_FILENO, &data->old_term);
	rl_catch_signals = 0;
}

void	close_unused_fds(int next)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->fds[1])
		close(data->fds[1]);
	if (data->oldfd)
		close(data->oldfd);
	if (next)
		data->oldfd = data->fds[0];
	else if (data->fds[0])
		close(data->fds[0]);
}
