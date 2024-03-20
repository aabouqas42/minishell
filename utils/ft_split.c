/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/20 22:40:38 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	*_strjoin(char *str1, char *str2);

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

char	**get_var(char **argv)
{
	char	*vars;
	char	*str;
	int		i;
	int		j;
	char	c;

	i = 0;
	while (argv[i])
	{
		str = NULL;
		if (ft_strchr(argv[i], '$'))
		{
			vars = argv[i];
			j = 0;
			while (vars && *vars)
			{
				if (vars[j] == '$')
				{
					j++;
					while (vars[j] && ft_isalnum(vars[j]))
						j++;
					c = vars[j];
					vars[j] = '\0';
					str = _strjoin(str, getenv(vars + 1));
				}
				else
				{
					while (vars[j] && vars[j] != '$')
						j++;
					c = vars[j];
					vars[j] = '\0';
					str = _strjoin(str, vars);
				}
				vars[j] = c;
				vars += j;
			}
			free (argv[i]);
			argv[i] = str;
		}
		i++;
	}
	return (argv);
}

size_t	_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (str && str[size])
		size++;
	return (size);
}

char	*_strjoin(char *str1, char *str2)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = _strlen(str1) + _strlen(str2);
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

// char	**get_var(char **argv)
// {
// 	int		i;
// 	int		j;
// 	char	c;
// 	char	*str;
// 	char	*s;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		str = NULL;
// 		if (ft_strchr(argv[i], '$') != NULL)
// 		{
// 			s = argv[i];
// 			while (*s)
// 			{
// 				j = 0;
// 				// rpfr rgterg      $PATH tgrt
// 				while (s[j] && ft_strchr("$ ", s[j]) == NULL)
// 					j++;
// 				// printf("%c", s[j]);
// 				// j += s[j] = ' ';
// 				// c = s[j];
// 				s[j] = '\0';
// 				// // printf("[%s]\n", s);
// 				str = _strjoin(str, s);
// 				// s[j] = c;
// 				s += j + 1;
// 			}
// 			printf("%s\n", str);
// 		}
// 		i++;
// 	}
// 	return (argv);
// }

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
	return (argv[i] = NULL, get_var(argv));
}
