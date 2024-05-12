/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cust_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:54:20 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/12 14:55:02 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
