/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/28 16:47:28 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_input(char **uin)
{
	char	*str;
	char	**args;
	char	qt;
	int		i;
	
	args = NULL;
	while(uin && *uin)
	{
		str = NULL;
		(1) && (i = 0, qt = 0);
		while ((*uin) && (*uin)[i])
		{
			if (((*uin)[i] == '\"' && qt != '\'') || ((*uin)[i] == '\'' && qt != '\"'))
			{
				qt = (qt == 0) * ((*uin)[i]);
				if (qt == 0)
					str = _strnjoin(str, "", 1);
			} else if ((*uin)[i] == '$' && qt == 0 && _strchr("\'\"", (*uin)[i + 1]) && (i++ || 1))
				continue;
			else if ((*uin)[i] == '$' && qt != '\'' && (ft_isalnum((*uin)[i + 1]) || ((*uin)[i + 1] && _strchr("_?", (*uin)[i + 1]))))
				i += set_var(*uin +i +1, &str);
			else
				str = _strnjoin(str, &((*uin)[i]), 1);
			i++;
		}
		if (str != NULL)
			args = _realloc(args, str);
		uin++;
	}
	free_tab(data_hook(NULL)->args);
	data_hook(NULL)->args = args;
}
