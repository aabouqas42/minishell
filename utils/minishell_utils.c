/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/21 15:20:10 by mait-elk         ###   ########.fr       */
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
	// free_tab(data->paths);
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
