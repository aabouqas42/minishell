/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/23 15:04:00 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_last_exit(char **str, t_data *data)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		safe_exit(-1);
	*str = _strjoin(*str, exit_status);
	return (0);
}

int	set_var(char *argv_str, char **str, t_data *data)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	if (*argv_str == '?')
		return (set_last_exit(str, data), 1);
	if (*argv_str == '$')
		return (*str = _strjoin(*str, ft_itoa(getpid())), 1);
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
	printf("[%s]\n", *str);
	if (*str == NULL)
		safe_exit(-1);
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
		vars = argv[i];
		if (ft_strchr(vars, '$'))
		{
			while (vars && *vars)
			{
				if (*vars == '$')
					(vars++, vars += set_var(vars, &str, data));
				else
					vars += set_word(vars, &str);
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
	while (i < (size_t)wc)
	{
		size = 0;
		while (*str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || dqt == 1))
			ft_switcher(&dqt,  str, size++);
		argv[i] = _strndup(str, size);
		if (argv[i++] == NULL)
			return (argv[size] = NULL, NULL);
		str += size;
	}
	return (argv[i] = NULL, get_var(argv, data), argv);
}
