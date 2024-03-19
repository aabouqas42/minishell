/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/19 23:09:23 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void ft_switcher(int *b, char *str, int size)
{
	if ((ft_strchr("\'\"", str[size]) && str[size - 1] != '\\')
		|| str[size] == '\\')
		*b = (*b == 0);
}

int	argument_count(char *str)
{
	size_t	wc;
	int		size;
	int		dqt;

	wc = 0;
	dqt = 0;
	while (str && *str)
	{
		size = 0;
		while (*str == ' ')
			str++;
		wc += (*str != '\0');
		while (str[size] && (str[size] != ' ' || dqt == 1))
		{
			ft_switcher(&dqt, str, size);
			size++;
		}
		if (dqt)
			return (-1);
		str += size;
	}
	return (wc);
}

char	*get_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_strchr(&str[i] , ' ') != NULL);
		}
		i++;
	}
}

size_t	get_size(char *str, int n)
{
	size_t	size;
	size_t	i;
	char	c;

	i = 0;
	size = 0;
	while (str[i] && i < n)
	{
		c = str[i];
		if (!ft_strchr("\"\'\\", c)
			|| (ft_strchr("\"\'\\", c) && str[i - 1] == '\\'))
			size++;
		// ipepriprgrpir $PATH 
		if (c == '$')
			
		i += (str[i - 1] == '\\');
		i++;
	}
	return (size);
}

char	*ft_strndup(char *str, size_t n)
{
	size_t	i;
	size_t	size;
	size_t	j;
	char	c;
	char	*res;

	if (str == NULL)
		return (NULL);
	i = 0;
	size = get_size(str, n);
	res = malloc(size + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		c = str[i];
		if (!ft_strchr("\"\'\\", c)
			|| (ft_strchr("\"\'\\", c) && str[i - 1] == '\\') )
				res[j++] = c;
		i += (str[i - 1] == '\\');
		i++;
	}
	return (res[j] = '\0', res);
}

char	**_split(char *str)
{
	char	**argv;
	int		dqt;
	size_t	size;
	int		wc;
	size_t	i;

	i = 0;
	dqt = 0;
	wc = argument_count(str);
	if (wc == -1)
		return (NULL);
	argv = malloc ((wc + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	while (i < wc)
	{
		size = 0;
		while (*str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || dqt == 1))
			ft_switcher(&dqt,  str, size++);
		argv[i] = ft_strndup(str, size);
		if (argv[i++] == NULL)
			return (argv[size] = NULL, NULL);
		str += size;
	}
	return (argv[i] = NULL, argv);
}
