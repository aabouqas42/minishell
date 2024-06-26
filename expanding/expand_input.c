/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:29 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/16 12:02:05 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_var(char curr_char, char next_char)
{
	if (curr_char == '$')
		if (ft_isalnum(next_char) || (next_char && _strchr("_?", next_char)))
			return (1);
	return (0);
}

int	set_last_exit(char **str)
{
	t_data	*data;
	char	*exit_status;

	data = data_hook(NULL);
	exit_status = ft_itoa(data->exit_status >> 8);
	if (exit_status == NULL)
		safe_exit(-1);
	*str = _strnjoin(*str, exit_status, _strlen(exit_status));
	free(exit_status);
	if (*str == NULL)
		safe_exit(-1);
	return (0);
}

int	set_var(char *argv_str, char **str)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	if (*argv_str == '?')
		return (set_last_exit(str), 1);
	if (ft_isdigit(argv_str[0]))
		return (1);
	while (argv_str[i] && (ft_isalnum(argv_str[i]) || argv_str[i] == '_'))
		i++;
	c = argv_str[i];
	argv_str[i] = '\0';
	tmp = env_grepvalue(argv_str);
	argv_str[i] = c;
	if (tmp != NULL)
	{
		*str = _strnjoin(*str, tmp, _strlenc(tmp, '\0'));
	}
	return (i);
}

char	*exp_with_no_qts(char *str, int herdoc)
{
	char	*ptr;
	char	*res;
	char	qt;

	(1337) && (qt = 0, res = NULL, ptr = str);
	while (str && *str != '\0')
	{
		if ((*str == DQT && qt != SQT) || (*str == SQT && qt != DQT))
		{
			qt = (qt == 0) * (*str);
			if (qt == 0)
				res = _strnjoin(res, "", 1);
		}
		else if (*str == '$' && _strchr("\'\"", *(str + 1)) && qt == 0)
		{
			str++;
			continue ;
		}
		else if (qt != SQT && is_var(*str, *(str + 1)) && herdoc == 0)
			str += set_var((str + 1), &res);
		else
			res = _strnjoin(res, str, 1);
		str++;
	}
	return (free (ptr), res);
}

char	*exp_with_qts(char *str, int herdoc)
{
	char	*ptr;
	char	*res;
	char	qt;

	(13 & 37) && (qt = 0, res = NULL, ptr = str);
	while (str && *str != '\0')
	{
		if ((*str == DQT && qt != SQT) || (*str == SQT && qt != DQT))
		{
			qt = (qt == 0) * (*str);
			if (fix_qt_err(str) && qt == 0)
				res = _strnjoin(res, "", 1);
		}
		if (*str == '$' && _strchr("\'\"", *(str + 1)) && qt == 0)
		{
			str++;
			continue ;
		}
		else if (qt != SQT && is_var(*str, *(str + 1)) && herdoc == 0)
			str += set_var((str + 1), &res);
		else
			res = _strnjoin(res, str, 1);
		str++;
	}
	return (free (ptr), res);
}
