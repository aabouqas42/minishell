/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/20 22:49:10 by aabouqas         ###   ########.fr       */
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
	user = ft_strjoin("\e[34m┌「 ", user);
	if (user == NULL)
		return (NULL);
	prompt = ft_strjoin(user, " ⫸ 1337.ma 」 \n└─$  \e[0m");
	free(user);
	if (prompt == NULL)
		return (NULL);
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
	while (env && data->env[i])
	{
		char	*value;
		char	c;

		value = ft_strchr(data->env[i], '=') + 1;
		c = *value;
		// printf("|%s|\n", getenv("PWD"));
		*(value -1) = '\0';
		env_export(data->env[i], value, data);
		i++;
	}
	return (0);
}
