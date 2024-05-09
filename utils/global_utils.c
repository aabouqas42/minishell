/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:12:23 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/09 12:24:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_arg_type	is_io_op(char	*str)
{
	if (str == NULL)
		return (None);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (ARG_APPEND);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (ARG_HERDOC);
	if (ft_strchr("<>|", *str) && *(str + 1) == 0)
	{
		if (ft_strchr("<", *str))
			return (ARG_REDIN);
		if (ft_strchr(">", *str))
			return (ARG_REDOUT);
		if (ft_strchr("|", *str))
			return (ARG_PIPE);
	}
	return (ARG_WORD);
}

t_arg	*get_last(t_arg *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

char	**_realloc(char **old_tab, char *to_append)
{
	char	**new_tab;
	size_t	tab_len;
	size_t	i;

	if (to_append == NULL)
		return (old_tab);
	if (old_tab == NULL)
	{
		new_tab = _calloc(2 * sizeof(char *));
		*new_tab = to_append;
		return (new_tab);
	}
	tab_len = 0;
	while (old_tab[tab_len])
		tab_len++;
	new_tab = _calloc((tab_len + 2) * sizeof(char *));
	i = 0;
	while (i < tab_len)
	{
		new_tab[i] = old_tab[i];
		i++;
	}
	free(old_tab);
	new_tab[i] = to_append;
	return (new_tab);
}

int	get_argsc(char **args)
{
	int	argsc;

	argsc = 0;
	while (args && args[argsc])
		argsc++;
	return (argsc);
}

void	print(int fd, char *str, int endl)
{
	size_t	size;

	size = _strlen(str);
	write (fd, str, size);
	if (endl)
		write(fd, "\n", 1);
}
