/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/27 11:13:31 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_input(char **usrinput)
{
	char	**res;
	char	*new_str;
	char	qt;
	int		i;
	int		j;
	
	res = NULL;
	new_str = NULL;
	j = 0;
	while(usrinput && *usrinput)
	{
		if (is_io_op(*usrinput))
			data_hook(NULL)->flags[j] = WORD_BIT;
		else
		if (ft_strchr(*usrinput, '$'))
		{
			i = 0;
			qt = 0;
			while ((*usrinput) && (*usrinput)[i])
			{
				if (((*usrinput)[i] == '\"' && qt != '\'') || ((*usrinput)[i] == '\'' && qt != '\"'))
					qt = (qt == 0) * ((*usrinput)[i]);
				if ((*usrinput)[i] == '$' && qt != '\'')
					i += set_var(&(*usrinput)[i + 1], &new_str);
				else if (qt != (*usrinput)[i])
					new_str = _strnjoin(new_str, *usrinput, 1);
				i++;
			}
		} else {
			res = _realloc(res, *usrinput);
		}
		j++;
		usrinput++;
	}
}
