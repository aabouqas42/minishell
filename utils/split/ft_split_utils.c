/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:03:36 by aabouqas          #+#    #+#             */
/*   Updated: 2024/03/27 03:44:16 by aabouqas         ###   ########.fr       */
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

int	set_word(char *argv_str, char **str, int sqt)
{
	int		i;
	char	c;

	i = 0;
	while ((argv_str[i] && argv_str[i] != '$' ) || sqt)
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
	int		dqt;
	int		sqt;

	if (str == NULL)
		return (NULL);
	res = NULL;
	sqt = 0;
	dqt = 0;
	while (*str)
	{
		if (*str == '\"' && !sqt)
			(dqt = !dqt);
		if (*str == '\'' && !dqt)
			(sqt = !sqt);
		printf("<%d %d -- %c>\n", sqt, dqt, *str);
		if (*str == '$' && (dqt || (!dqt && !sqt)))
			(str++, str += set_var(str, &res));
		else
			str += set_word(str, &res, sqt);
	}
	printf("@@%s>>\n", res);
	res = handle_dqt_sqt(res);
	return (res);
}
