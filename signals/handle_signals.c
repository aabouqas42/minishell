/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:10:00 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/13 16:43:54 by aabouqas         ###   ########.fr       */
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

	(void)sig;
	data = data_hook(NULL);
	if (data && data->fix_doubleprt == 2)
	{
		close(0);
		return ;
	}
	if (data && data->fix_doubleprt)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_signals(void)
{
	signal(SIGINT, sig_handle_sigint);
	signal(SIGQUIT, sig_handle_sigquit);
}
