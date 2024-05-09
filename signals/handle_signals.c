/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:10:00 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/09 15:28:56 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handle_sigquit(int sig)
{
	(void)sig;
}

void	sig_handle_sigint(int sig)
{
	t_data	*data;

	data = data_hook(NULL);
	printf("\n");
	(void)sig;
	if (data && data->fix_doubleprt)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_signals(void)
{
	signal(SIGINT, sig_handle_sigint);
	signal(SIGQUIT, sig_handle_sigquit);
}
