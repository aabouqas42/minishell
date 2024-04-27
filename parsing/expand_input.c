/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/26 12:11:57 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_input(char **usrinput)
{
	char	**res;
	char	*new_str;
	char	qt;
	int		i;
	
	res = NULL;
	while(usrinput && *usrinput)
	{
		if (ft_strchr(*usrinput, '$'))
		{
			i = 0;
			qt = 0;
			new_str = NULL;
			while ((*usrinput) && (*usrinput)[i]) {
				if (((*usrinput)[i] == '\"' && qt != '\'') || ((*usrinput)[i] == '\'' && qt != '\"'))
					qt = (qt == 0) * ((*usrinput)[i]);
				if ((*usrinput)[i] == '$' && qt != '\'')
				{
					i++; // to skip character '$'
					i += set_var(&(*usrinput)[i], &new_str);
				}
				else
					new_str = _strnjoin(new_str, &((*usrinput)[i++]), 1); // to skip the one char joined
			}
			// printf("EXPANDED:[%s]\n", new_str);
			res = _realloc(res, new_str);
		}else
			res = _realloc(res, *usrinput);
		usrinput++;
	}
}
