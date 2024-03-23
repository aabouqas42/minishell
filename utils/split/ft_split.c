/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/22 22:23:36 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_last_exit(char **str, t_data *data)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		return (_free(data), exit(-1), -1);
	*str = _strjoin(*str, exit_status);
	return (0);
}

int	set_var(char *argv_str, char **str, t_data *data)
{
	int		i;
	char	c;

	i = 0;
	if (*argv_str == '?')
	{
		argv_str++;
		set_last_exit(str, data);
		return (1);
	}
	while (argv_str[i] && ft_isalnum(argv_str[i]))
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	*str = _strjoin(*str, getenv(argv_str));
	if (*str == NULL)
		(_free(data), exit(-1));
	argv_str[i] = c;
	return (i);
}

int	set_word(char *argv_str, char **str, t_data *data)
{
	int		i;
	char	c;

	i = 0;
	while (argv_str[i] && argv_str[i] != '$')
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	*str = _strjoin(*str, argv_str);
	printf("[%s]\n", *str);
	if (*str == NULL)
		(_free(data), exit(-1));
	argv_str[i] = c;
	return (i);
}

void	get_var(char **argv, t_data *data)
{
	char	*vars;
	char	*str;
	int		i;

	i = 0;
	while (argv[i])
	{
		str = NULL;
		if (ft_strchr(argv[i], '$'))
		{
			vars = argv[i];
			while (*vars)
			{
				if (*vars == '$')
					(vars++, vars += set_var(vars, &str, data));
				else
					vars += set_word(vars, &str, data);
			}
			free (argv[i]);
			argv[i] = str;
		}
		i++;
	}
}

char	**_split(char *str, t_data *data)
{
	char	**argv;
	size_t	size;
	size_t	i;
	int		dqt;
	int		wc;

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
	get_var(argv, data);
	return (argv[i] = NULL, argv);
}
