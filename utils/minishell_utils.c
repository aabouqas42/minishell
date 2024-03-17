/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/17 03:58:45 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	free_tab(char **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	_free(t_data *data)
{
	free (data->line);
	free (data->program_path);
	free_tab(data->argv);
	free_tab(data->paths);
	free (data->promte);
}

char	*get_promte()
{
	char	*promte;
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		user = "mait-aabouqas";
	promte = ft_strjoin(user, "@1337 $ ");
	if (promte == NULL)
		return (free (user), NULL);
	return (promte);
}

int	data_init(t_data *data, char **env)
{
	char	*paths;
	int		i;

	data->argv = NULL;
	data->line = NULL;
	data->program_path = NULL;
	data->paths = NULL;
	data->env = env;
	data->promte = get_promte();
	paths = get_paths_env(data);
	data->paths = ft_split(paths, ':');
	if (data->paths == NULL)
	{
		_free(data);
		exit(-1);
	}
	i = 0;
	while (data->env[i])
	{
		char **env = ft_split((const char *)data->env[i], '=');
		env_export(env[0], env[1], &data->_env);
		free (env[0]);
		free (env[1]);
		i++;
	}
	return (0);
}
