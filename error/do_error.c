/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:46:47 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/03 18:41:57 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_error(t_error_type errtype, char *reason)
{
	if (errtype == SYNTAX_ERR)
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd("'\n", 2);
		data_hook(NULL)->exit_status = 258 << 8;
	}
	if (errtype == PERMIDEN_ERR)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data_hook(NULL)->exit_status = 126 << 8;
	}
	if (errtype == COMDNF_ERR)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd(": command not found\n", 2);
		data_hook(NULL)->exit_status = 127 << 8;
	}
	if (errtype == ISDIR_ERR)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd(": is a directory\n", 2);
		data_hook(NULL)->exit_status = 126 << 8;
	}
	if (errtype == NSFODIR_ERR)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data_hook(NULL)->exit_status = 127 << 8;
	}
	if (errtype == AMBIGUOUS_ERR)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(reason, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		data_hook(NULL)->exit_status = 127 << 8;
	}
}
