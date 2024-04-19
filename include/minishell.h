/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/19 10:27:31 by aabouqas         ###   ########.fr       */
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

typedef enum e_error_type{
	SYNTAX_ERR,
	COMDNF_ERR
}	t_error_type;

void	do_error(t_error_type errtype);

#define LOG(v) printf("%s\n", v)

#define MSG_SYNTAX_ERR "Syntax Error"
#define MSG_COMMAND_ERR "Command Not Found"

typedef enum e_cmd_type
{
	None,
	CMD_TYPE_COMMAND,
	CMD_TYPE_PIPE,
	CMD_TYPE_SREDIRECTION,
	CMD_TYPE_DREDIRECTION
}	t_cmd_type;

typedef struct s_cmd
{
	char		**argv;
	t_cmd_type	cmd_type;
}	t_cmd;


typedef struct s_qutoes
{
	int	sqt;
	int	dqt;
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

typedef enum e_action
{
	Void,
	Pipe,
	Redirect_in,
	Redirect_out,
	Append_in,
	Append_out
	
}	t_action;

typedef struct	s_list_args
{
	char				**argv;
	char				**env;
	char				*program_path;
	t_action			action;
	int					_out;
	int					_in;
	struct s_list_args	*next;
}	t_list_args;

typedef struct s_data
{
	t_env		*env;
	char		**commands;
	char		*prompt;
	char		*line;
	char		*program_path;
	int			exit_status;
	t_list_args	*list;
}	t_data;

#define ENV_NOT_CREATED -1
#define ENV_FAILURE 0
#define ENV_CREATED 1

char	**env_to_2darray();

int		env_export(char *name, char *value);
t_env	*env_create(char *name, char *value);
t_env	*env_get(char *name, t_data	*data);
int		env_unset(char *name, t_env **env);
t_env	*env_get_last(t_env	*env);
void	env_sort(t_env *env);
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

int		is_valid_cmd(t_data *data, char *cmd);
void	safe_exit(int status);
void	free_tab(char **array);
char	**_split(char *str);
char	*_strndup(char *str);
// char	*_strjoin(char *str1, char *str2);
char	*_strnjoin(char *str1, char *str2, size_t size);
int	is_same(char *s1, char *s2);
size_t	p_strlenc(char *str, char c);
char	*p_strdup(char *s1);
size_t	argument_count(char *str);

int		cd(t_data *data);
void	echo();
int		pwd();
int		_export();
int		_redirection();
size_t	get_size(char *str);
char	*handle_dqt_sqt(char *str);
void	*p_calloc(size_t size);
char	*_expander(char *str);
int		_spaces(int c);
int		request_input();

int		set_var(char *argv_str, char **str);
size_t	args_is_valid(char *str);
char	**_realloc(char **old_tab, char *to_append);

void		add(t_list_args **head);
t_list_args	*create();
t_list_args	*get_first();
t_list_args	*get_last(t_list_args *head);

#endif
