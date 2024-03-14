/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/14 15:45:47 by aabouqas         ###   ########.fr       */
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

	data->argv = NULL;
	data->line = NULL;
	data->program_path = NULL;
	data->program_env = NULL;
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
	return (0);
}
