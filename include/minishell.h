/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/22 19:20:08 by mait-elk         ###   ########.fr       */
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
# include <fcntl.h>
# include <dirent.h>

# define P printf

typedef enum e_error_type{
	SYNTAX_ERR,
	COMDNF_ERR
}	t_error_type;

void	do_error(t_error_type errtype);

typedef struct s_qutoes
{
	int	sqt;
	int	dqt;
}	t_qutoes; 


/*	ENV LIST	*/
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char		***cmds;
	t_env		*env;
	char		**commands;
	char		*prompt;
	char		*usrinput;
	char		*program_path;
	int			exit_status;
	int			in;
	int			out;
	int			oldfd;
	int			fds[2];
}	t_data;

char	**env_to_2darray();

int		env_export(char *name, char *value);
t_env	*env_create(char *name, char *value);
t_env	*env_get(char *name, t_data	*data);
int		env_unset(char *name, t_env **env);
t_env	*env_get_last(t_env	*env);
void	env_sort(t_env *env);
char	***get_commands();
void	data_init(char **base_env);
void	set_defaults();
void	free_matrix(char ***matrix);
int		env_valid_name(char *name);
void	env_print(t_env	*head);
size_t	env_size(t_env *env);
void	env_free(t_env *env);
void	env_free_list(t_env *env);
char	*env_grepvalue(char *name);

t_data	*data_hook(t_data *data);

int		is_io_op(char	*str);

/*	END ENV LIST	*/


char	*get_prompt();
int		check_input();

int		is_valid_cmd(t_data *data, char *cmd);
void	safe_exit(int status);
void	free_tab(char **array);
char	**_split(char *str);
char	*_strnjoin(char *str1, char *str2, size_t size);
int		is_same(char *s1, char *s2);
size_t	_strlenc(char *str, char c);
char	*_strdup(char *s1);
char	*_strndup(char *s1, size_t size);
int		cd(t_data *data);
void	echo();
int		pwd();
int		_export();
int		_redirection();
void	*_calloc(size_t size);
char	*_expander(char *str);
int		_spaces(int c);
int		request_input();

int		set_var(char *argv_str, char **str);
size_t	args_is_valid(char *str);
char	**_realloc(char **old_tab, char *to_append);

#endif
