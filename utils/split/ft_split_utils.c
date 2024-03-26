/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/26 17:23:36 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	argument_count(char *str)
{
	size_t	wc;
	int		i;
	int		dqt;
	int		sqt;

	wc = 0;
	dqt = 0;
	sqt = 0;
	while (str && *str)
	{
		i = 0;
		while (*str && *str == ' ')
			str++;
		wc += (*str != '\0');
		while (str[i] && (str[i] != ' ' || dqt || sqt))
		{
			(str[i] == '\"' && !sqt) && (dqt = !dqt);
			(str[i] == '\'' && !dqt) && (sqt = !sqt);
			i++;
		}
		if (dqt || sqt)
			return (0);
		str += i;
	}
	return (wc);
}

char	*_strjoin(char *str1, char *str2)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = _nsx_strlen(str1) + _nsx_strlen(str2);
	str = malloc (len + 1);
	if (str == NULL)
		return (free (str1), NULL);
	i = 0;
	while (str1 && str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (str2 && *str2)
	{
		str[i] = *str2;
		i++;
		str2++;
	}
	str[i] = '\0';
	return (free (str1), str);
}

int	set_var(char *argv_str, char **str)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	if (*argv_str == '\0')
		return (0);
	// if (*argv_str == '?')
	// 	return (set_last_exit(str, data), 1);
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

int	set_word(char *argv_str, char **str, int sqt)
{
	int		i;
	char	c;

	i = 0;
	while (argv_str[i] && (argv_str[i] != '$' || sqt))
	{
		i++;
	}
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
	int		dqt;
	int		sqt;

	if (str == NULL)
		return (NULL);
	res = NULL;
	sqt = 0;
	dqt = 0;
	// printf("((%s))\n", str);
	while (*str)
	{
		if (*str == '\"' && !sqt) 
		{
			(dqt = !dqt);
		}
		if (*str == '\'' && !dqt) 
		{
			(sqt = !sqt);
		}
		if (*str == '$' && (dqt || (!dqt && !sqt)))
			(str++, str += set_var(str, &res));
		else
			str += set_word(str, &res, sqt);
	}
	return (res);
}
