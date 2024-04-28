/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/04/28 19:21:46 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_case(char *str)
{
	return (*str == '$' && _strchr("\'\"" , *(str + 1)));
}

int	var_case(char *s)
{
	if (*s == '$')
		if (ft_isalnum(*(s + 1)) || (*(s + 1) && _strchr("_?", *(s + 1))))
				return (1);
	return (0);
}

void	expand_input(char **uin)
{
	char	*str;
	char	*arg;
	char	**args;
	char	qt;
	int		i;
	
	args = NULL;
	while(uin && *uin)
	{
		(1) && (i = -1, qt = 0, str = NULL);
		while ((*uin) && (*uin)[++i])
		{
			arg = *uin;
			if ((arg[i] == '\"' && qt != '\'') || (arg[i] == '\'' && qt != '\"'))
			{
				qt = (qt == 0) * (arg[i]);
				(1) && (qt == 0 && (str = _strnjoin(str, "", 1)));
			} else if (skip_case(arg + i) && qt == 0 && (1 || i++))
				continue ;
			else if (qt != '\'' && var_case(arg + i))
				i += set_var(*uin + i + 1, &str);
			else
				str = _strnjoin(str, arg + i, 1);
		}
		(1) && (str != NULL) && (args = _realloc(args, str), uin++);
	}
	free_tab(data_hook(NULL)->args);
	data_hook(NULL)->args = args;
}
