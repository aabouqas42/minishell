/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/24 14:09:53 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

t_data	*data_hook(t_data *data)
{
	static t_data	*data_saved;

	if (data != NULL)
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

	data = data_hook(NULL);
	free (data->line);
	data->line = NULL;
	free (data->program_path);
	data->program_path = NULL;
	free_tab(data->argv);
	free (data->prompt);
	exit(status);
}

char	*get_prompt()
{
	// char	*prompt;
	// char	*user;

	// user = getenv("USER");
	// if (user == NULL || *user == '\0')
	// 	user = "unknown";
	// user = ft_strjoin("\e[34m┌「 ", user);
	// if (user == NULL)
	// 	safe_exit(-1);
	// prompt = ft_strjoin(user, " ⫸  1337.ma 」 \n└─$  \e[0m");
	// free(user);
	// if (prompt == NULL)
	// 	safe_exit(-1);
	// return (prompt);
	return ("$>> ");
}
