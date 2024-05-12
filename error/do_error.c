/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:46:47 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/11 10:38:47 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	__syntax_err(char *reason)
{
	print(2, "minishell : syntax error near unexpected token `", 0);
	print(2, reason, 0);
	print(2, "'", 1);
	data_hook(NULL)->exit_status = 258 << 8;
}

static void	__invnameenv_err(char *progname, char *reason)
{
	print(2, "minishell : ", 0);
	print(2, progname, 0);
	print(2, ": `", 0);
	print(2, reason, 0);
	print(2, "': not a valid identifier", 1);
	data_hook(NULL)->exit_status = 127 << 8;
}

static void	__notdirectory_err(char *progname, char *reason)
{
	print(2, "minishell : ", 0);
	print(2, progname, 0);
	print(2, ": `", 0);
	print(2, reason, 0);
	print(2, ": Not a directory", 1);
	data_hook(NULL)->exit_status = 1 << 8;
}

static void	__custom_err(char *lmsg, char *reason, int e)
{
	print(2, "minishell : ", 0);
	print(2, reason, 0);
	print(2, lmsg, 1);
	data_hook(NULL)->exit_status = e << 8;
}

void	custom_err(char *progname, char *reason, char *msg, int es)
{
	print(2, "minishell: ", 0);
	print(2, progname, 0);
	print(2, ": ", 0);
	print(2, reason, 0);
	print(2, ": ", 0);
	print(2, msg, 1);
	data_hook(NULL)->exit_status = es << 8;
}


void	do_error(t_error_type errtype, char *progname, char *reason)
{
	if (errtype == SYNTAX_ERR)
		__syntax_err(reason);
	if (errtype == INVNAMEENV_ERR)
		__invnameenv_err(progname, reason);
	if (errtype == NOTDIRECTORY_ERR)
		__notdirectory_err(progname, reason);
	if (errtype == PERMIDEN_ERR)
		__custom_err(": Permission denied", reason, 126);
	if (errtype == COMDNF_ERR)
		__custom_err(": command not found", reason, 127);
	if (errtype == ISDIR_ERR)
		__custom_err(": is a directory", reason, 126);
	if (errtype == NSFODIR_ERR)
		__custom_err(": No such file or directory", reason, 127);
	if (errtype == AMBIGUOUS_ERR)
		__custom_err(": ambiguous redirect", reason, 127);
}
