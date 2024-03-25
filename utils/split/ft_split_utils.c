/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/25 16:42:24 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	argument_count(char *str)
{
	size_t	wc;
	int		i;
	int		dqt;

	wc = 0;
	dqt = 0;
	while (str && *str)
	{
		i = 0;
		while (*str && *str == ' ')
			str++;
		wc += (*str != '\0');
		while (str[i] && (str[i] != ' ' || dqt == 1))
		{
			if (str[i] == '\"')
				dqt = (dqt == 0);
			i++;
		}
		if (dqt)
			return (0);
		str += i;
	}
	return (wc);
}

size_t	get_size(char *str, int n)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	while (str[i] && i < n)
	{
		size++;
		i++;
	}
	return (size);
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
	if (i == 0)
		return (1);
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

int	set_word(char *argv_str, char **str)
{
	int		i;
	char	c;

	i = 0;
	while (argv_str[i] && argv_str[i] != '$')
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	*str = _strjoin(*str, argv_str);
	if (*str == NULL)
		safe_exit(-1);
	argv_str[i] = c;
	return (i);
}

char	*_strndup(char *str, size_t n)
{
	size_t	i;
	size_t	size;
	char	c;
	char	*res;

	if (str == NULL)
		return (NULL);
	i = 0;
	size = get_size(str, n);
	res = NULL;
	i = 0;
	c = str[size];
	str[size] = '\0';
	printf("%s given < \n", str);
	while (str[i])
	{
		if (str[i] == '$')
			(i++, i += set_var(&str[i], &res));
		else
			i += set_word(&str[i], &res);
	}
	str[size] = c;
	return (res);
}
