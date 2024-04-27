/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/27 09:24:42 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_input(char **usrinput)
{
	char	*new_str;
	char	qt;
	int		i;
	
	while(usrinput && *usrinput)
	{
		new_str = NULL;
		(1) && (i = 0, qt = 0);
		while ((*usrinput) && (*usrinput)[i])
		{
			if (((*usrinput)[i] == '\"' && qt != '\'') || ((*usrinput)[i] == '\'' && qt != '\"'))
			{
				qt = (qt == 0) * ((*usrinput)[i]);
				if (qt == 0)
					new_str = _strnjoin(new_str, "", 1);
			}
			else if ((*usrinput)[i] == '$' && qt != '\'')
				i += set_var(*usrinput +i +1, &new_str);
			else
				new_str = _strnjoin(new_str, &((*usrinput)[i]), 1);
			i++;
		}
		(1) && (free (*usrinput), *usrinput = new_str);
		usrinput++;
	}
}
