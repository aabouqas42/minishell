/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:07:50 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/26 00:41:04 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_last_exit(char **str, t_data *data)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		safe_exit(-1);
	*str = _strnjoin(*str, exit_status, _strlen(exit_status, '\0'));
	return (0);
}

int	set_var(char *argv_str, char **str, t_data *data)
{
	int		size;
	char	*tmp;
	char	*pid;

	(void)data;
	printf("%s\n", argv_str);
	size = 0;
	if (*argv_str == '\0')
		return (0);
	// if (*argv_str == '?')
	// 	return (set_last_exit(str, data), 1);
	if (*argv_str == '$')
	{
		pid = ft_itoa(getpid());
		*str = _strnjoin(*str, pid, _strlen(pid, '\0'));
		return (free(pid), 1);
	}
	while (argv_str[size] && (ft_isalnum(argv_str[size]) || argv_str[size] == '_'))
		size++;
	if (size == 0)
		return (1);
	tmp = env_grepvalue(argv_str); 
	printf("%d\n", size);
	*str = _strnjoin(*str, tmp, size);
	if (*str == NULL)
		safe_exit(-1);
	return (size);
}

int	set_word(char *argv_str, char **str)
{
	int		i;

	i = 0;
	while (argv_str[i] && argv_str[i] != '$')
		i++;
	*str = _strnjoin(*str, argv_str, i);
	if (*str == NULL)
		safe_exit(-1);
	return (i);
}

void	get_var(char **argv, t_data *data)
{
	char	*vars;
	char	*str;
	int		inRange;
	int		i;

	i = 0;
	inRange = 0;
	while (argv[i])
	{
		str = NULL;
		vars = argv[i];
		if (ft_strchr(vars, '$'))
		{
			while (vars && *vars)
			{
				if (*vars == '$' && !inRange)
					(vars += set_var(vars + 1, &str, data), vars++);
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
	size_t	wc;

	i = 0;
	dqt = 0;
	wc = argument_count(str);
	if (wc == 0)
		return (printf("Invalid Args\n"), NULL);
	argv = malloc (sizeof(char *) * (wc + 1));
	if (argv == NULL)
		safe_exit(-1);
	while (i < wc)
	{
		size = 0;
		while (*str == ' ')
			str++;
		while (str[size] && (str[size] != ' ' || dqt == 1))
		{
			if (str[size] == '\"')
				dqt = (dqt == 0);
			size++;
		}
		argv[i] = _strndup(str, size);
		if (argv[i++] == NULL)
			return (argv[size] = NULL, NULL);
		str += size;
	}
	(void)data;
	return (argv[i] = NULL, /*get_var(argv, data),*/ argv);
}
