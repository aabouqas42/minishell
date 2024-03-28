/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/28 01:44:42 by aabouqas         ###   ########.fr       */
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

int	set_last_exit(char **str)
{
	t_data *data;
	char	*exit_status;

	data = data_hook(NULL);
	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		safe_exit(-1);
	*str = _strjoin(*str, exit_status);
	if (*str == NULL)
		safe_exit(-1);
	data->exit_status = 0;
	return (0);
}

int	set_var(char *argv_str, char **str)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	if (*argv_str == '\0')
		return (0);
	if (*argv_str == '?')
		return (set_last_exit(str), 1);
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

char	*init_res(char *res)
{
	char	*r;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (res && res[i])
	{
		if (ft_isprint(res[i]))
			size++;
		i++;
	}
	r = p_calloc(size + 1);
	i = 0;
	size = 0;
	while (res && res[i])
	{
		if (ft_isprint(res[i]))
			r[size++] = res[i];
		i++;
	}
	free(res);
	return (r);
}

char	*_expander(char *str)
{
	char	*res;
	int		sqt;

	if (str == NULL)
		return (NULL);
	res = NULL;
	sqt = 0;
	while (*str)
	{
		if (*str == 1)
			sqt = (sqt == 0);
		if (*str == '$' && *(str + 1) != '\0' && sqt == 0)
			(str++, str += set_var(str, &res));
		else
			res = _strnjoin(res, str++, 1);
	}
	res = init_res(res);
	return (res);
}
