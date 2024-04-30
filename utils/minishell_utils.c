/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:06:16 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/30 19:24:20 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"
#include <stdio.h>

t_data	*data_hook(t_data *data)
{
	static t_data	*data_saved;

	if (data != NULL)
		data_saved = data;
	return (data_saved);
}

void	do_error(t_error_type errtype, char *reason)
{
	if (errtype == SYNTAX_ERR)
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd("'\n", 2);
		data_hook(NULL)->exit_status = 258 << 8;
		return ;
	}
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(reason, 2);
	if (errtype == COMDNF_ERR)
		ft_putstr_fd(": command not found\n", 2);
	if (errtype == ISDIR_ERR)
	{
		ft_putstr_fd(": is a directory\n", 2);
		data_hook(NULL)->exit_status = 126 << 8;
	}
	if (errtype == NSFODIR_ERR)
		ft_putstr_fd(": No such file or directory\n", 2);
	if (errtype == AMBIGUOUS_ERR)
		ft_putstr_fd(": ambiguous redirect\n", 2);
	if ((errtype == NSFODIR_ERR)
		|| (errtype == AMBIGUOUS_ERR)
		|| (errtype == COMDNF_ERR))
		data_hook(NULL)->exit_status = 127 << 8;
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
	free_tab(data->args);
	// env_free_list(data->env);
	data->args = NULL;
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
	return ("mait-elk@e3r3p16.1337.ma $> ");
}
