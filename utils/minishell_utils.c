/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/17 15:28:10 by mait-elk         ###   ########.fr       */
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
	free (data->prompt);
}

char	*get_prompt()
{
	char	*prompt;
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		user = "mait-aabouqas";
	prompt = ft_strjoin(user, "@1337 $ ");
	if (prompt == NULL)
		return (free (user), NULL);
	return (prompt);
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
	data->prompt = get_prompt();
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
