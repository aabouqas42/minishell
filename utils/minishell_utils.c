/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/21 13:16:45 by aabouqas         ###   ########.fr       */
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

void	do_error(t_error_type errtype)
{
	char	*err;

	if (errtype == SYNTAX_ERR)
	{
		err = "Error : minishell : Syntax ERROR\n";
		data_hook(NULL)->exit_status = 256 << 8;
	}
	if (errtype == COMDNF_ERR)
	{
		err = "Error : minishell : Command Not Found\n";
		data_hook(NULL)->exit_status = 127 << 8;
	}
	ft_putstr_fd(err, 2);
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
	free (data->usrinput);
	data->usrinput = NULL;
	free (data->program_path);
	data->program_path = NULL;
	free_tab(data->commands);
	// env_free_list(data->env);
	data->commands = NULL;
	// free (data->prompt); #BUS ERROR ?
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
	return ("mait-elk@1337.ma $> ");
}
