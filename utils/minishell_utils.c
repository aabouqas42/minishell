/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/23 12:10:27 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

t_data	*data_hook(t_data *data, int just_read)
{
	static t_data	*data_saved;

	if (!just_read)
		data_saved = data;
	return (data_saved);
}

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

void	safe_exit(int status)
{
	t_data *data;

	data = data_hook(NULL, 1);
	free (data->line);
	free (data->program_path);
	free_tab(data->argv);
	// free_tab(data->paths);
	free (data->prompt);
	exit(status);
}

char	*get_prompt()
{
	char	*prompt;
	char	*user;

	user = getenv("USER");
	if (user == NULL || *user == '\0')
		user = "unknown";
	user = ft_strjoin("\e[34m┌「 ", user);
	if (user == NULL)
		safe_exit(-1);
	prompt = ft_strjoin(user, " ⫸  1337.ma 」 \n└─$  \e[0m");
	free(user);
	if (prompt == NULL)
		safe_exit(-1);
	return (prompt);
}

size_t	p_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
