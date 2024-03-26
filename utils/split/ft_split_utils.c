/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/26 03:55:03 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	argument_count(char *str)
{
	size_t	wc;
	int		i;
	char	dqt;

	wc = 0;
	dqt = 0;
	while (str && *str)
	{
		i = 0;
		while (*str && *str == ' ')
			str++;
		wc += (*str != '\0');
		while (str[i] && (str[i] != ' ' || dqt))
		{
			if (ft_strchr("\"\'", str[i]))
			{
				if (str[i] == '\"')
					dqt |= (dqt & 0b10000000);
				else
					dqt |= (dqt & 0b01000000);
			}
			i++;
		}
		if (dqt)
			return (0);
		str += i;
	}
	return (wc);
}

int	set_var(char *argv_str, char **str)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	while (argv_str[i] && (ft_isalnum(argv_str[i]) || argv_str[i] == '_'))
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	tmp = env_grepvalue(argv_str);
	if (tmp == NULL)
		tmp = "";
	*str = _strjoin(*str, tmp);
	if (*str == NULL)
		safe_exit(-1);
	argv_str[i] = c;
	return (i);
}

int	set_word(char *argv_str, char **str, int cond)
{
	int		i;
	char	c;

	i = 0;
	while (argv_str[i] && (argv_str[i] != '$' || cond))
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	*str = _strjoin(*str, argv_str);
	if (*str == NULL)
		safe_exit(-1);
	argv_str[i] = c;
	return (i);
}

char	*_strndup(char *str)
{
	char	*res;
	int		qt;

	qt = 0;
	if (str == NULL)
		return (NULL);
	res = NULL;
	while (ft_strchr(str, '\"'))
		*ft_strchr(str, '\"') = 127;
	// printf("%s\n", str);
	while (*str)
	{
		if (*str == '\'')
			qt = (qt == 0);
		if (*str == '$' && qt == 0)
			(str++, str += set_var(str, &res));
		else
			str += set_word(str, &res, qt);
	}
	while (ft_strchr(res, '\''))
		*ft_strchr(res, '\'') = 127;
	return (res);
}
