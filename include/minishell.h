/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/27 03:09:05 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_qutoes
{
	int	_single;
	int	_double;
}	t_qutoes;

// # include "dirent.h" ?? 

# define CMD_FAIL -1
# define CMD_INVALID 0
# define CMD_VALID 1

/*	ENV LIST	*/
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env		*env;
	char		**argv;
	char		*prompt;
	char		*line;
	char		*program_path;
	int			exit_status;
}	t_data;

#define ENV_NOT_CREATED -1
#define ENV_FAILURE 0
#define ENV_CREATED 1

int		env_export(char *name, char *value, t_data *data);
t_env	*env_create(char *name, char *value);
t_env	*env_get(char *name, t_data	*data);
int		env_unset(char *name, t_env **env);
t_env	*env_get_last(t_env	*env);
void	env_sort(t_env *env);
int		env_valid_name(char *name);
void	env_print(t_env	*head);
size_t	env_size(t_env *env);
void	env_free(t_env *env);
char	*env_grepvalue(char *name);

t_data	*data_hook(t_data *data);

/*	END ENV LIST	*/


char	*get_prompt();

int		is_valid_cmd(t_data *data, char *cmd);
void	safe_exit(int status);
void	free_tab(char **array);
char	*get_paths_env();
char	**_split(char *str);
char	*_strndup(char *str);
char	*_strjoin(char *str1, char *str2);
int		_strcmp(char *s1, char *s2);
size_t	_strlen(char *str);
char	*_strdup(char *s1);
size_t	argument_count(char *str);

int		cd(t_data *data);
void	echo(t_data *data);
int		pwd();
int		_export(t_data *data);

void	*p_calloc(size_t size);

#endif
