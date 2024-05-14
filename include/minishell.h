/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/14 17:02:37 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <errno.h>
# define _FILE 1
# define _DIRE 2
# define DQT '\"'
# define SQT '\''

typedef enum e_arg_type
{
	None = -1,
	ARG_WORD,
	ARG_QT,
	ARG_PIPE,
	ARG_REDOUT,
	ARG_REDIN,
	ARG_APPEND,
	ARG_HERDOC
}	t_arg_type;

typedef enum e_error_type
{
	SYNTAX_ERR,
	COMDNF_ERR,
	ISDIR_ERR,
	NSFODIR_ERR,
	AMBIGUOUS_ERR,
	PERMIDEN_ERR,
	INVNAMEENV_ERR,
	NOTDIRECTORY_ERR,
	ARGNUMREQ_ERR
}	t_error_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_flag
{
	int	inide_qts;
	int	is_io_op;
	int	out;
	int	in;
}	t_flag;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*list;
	t_arg_type		type;
	struct s_arg	*next;
}	t_arg;

typedef struct s_cmd
{
	t_arg			*linked_argv;
	char			**argv;
	int				in;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmds;
	t_env			*env;
	t_arg			*args;
	struct termios	old_term;
	char			**env_2d;
	char			*pwd;
	char			*prompt;
	char			*usrinput;
	char			*program_path;
	int				exit_status;
	int				oldfd;
	int				fix_doubleprt;
	int				def_in;
	int				def_out;
	int				fds[2];
}	t_data;

/**
 * KIIIING HELPERS :)
*/
t_data		*data_hook(t_data *data);
void		safe_exit(int status);

/**
 * T_ARG INSTRACTIONS
 */
void		t_arg_put(char *value, t_arg_type type, t_arg **head);
void		t_arg_add(char *value, t_arg_type type);
t_arg		*t_arg_get_last(t_arg *head);
size_t		t_arg_size(t_arg *head);
void		t_arg_free(t_arg *head);

/**
 * T_CMD INSTRACTIONS
 */
void		t_cmd_add(t_cmd to_add);
void		t_cmd_free(t_cmd *head);

/**
 * SIGNALS FUNCTIONS
 */
void		sig_handle_sigquit(int sig);
void		sig_handle_sigint(int sig);
void		catch_signals(void);

/**
 * ENV FUNCTIONS
*/
t_env		*env_create(char *name, char *value);
int			env_export(char *name, char *value);
t_env		*env_get(char *name, t_data	*data);
int			env_unset(char *name, t_env **env);
int			env_valid_name(char *name);
char		*env_grepvalue(char *name);
t_env		*env_get_last(t_env	*env);
void		env_free_list(t_env *env);
void		env_print(t_env	*head);
size_t		env_size(t_env *env);
void		env_sort(t_env *env);
void		env_free(t_env *env);
void		init_env_array(void);

/**
 * ADV LIBFT FUNCTIONS
*/
char		*_strnjoin(char *str1, char *str2, size_t size);
char		**_realloc(char **old_tab, char *to_append);
void		print(int fd, char *str, int endl);
char		*_strjoin(char *str1, char *str2);
char		*_strndup(char *s1, size_t size);
size_t		_strlenc(char *str, char c);
int			str_equal(char *s1, char *s2);
char		*_strchr(char *s, char c);
void		*_calloc(size_t size);
char		*skiper(char *str);
size_t		_strlen(char *str);
char		*_strdup(char *s1);
int			_spaces(int c);

/**
 * BUILT-INS FUNCTIONS
*/
int			run_builtin(t_cmd *cmd);
int			is_builtin(t_cmd *cmd);
int			builtins(t_cmd *cmd);
int			_export(char **argv);
void		__exit(t_cmd *cmd);
int			unset(char **argv);
void		echo(char **argv);
int			cd(char **argv);
int			pwd(void);

/**
 * ERRORS HANDLING
*/
void		do_error(t_error_type errtype, char *progname, char *reason);
void		custom_err(char *progname, char *reason, char *msg, int es);
void		check_arguments(int ac, char **av);

/**
 * 	IO OPERATORS
*/
void		set_pipes(t_cmd *cmd, int first, int next);
int			is_var(char curr_char, char next_char);
int			is_valid_cmd(t_data *data, char *cmd);
int			set_var(char *argv_str, char **str);
char		*exp_with_no_qts(char *str, int hd);
char		*exp_with_qts(char *str, int hd);
int			check_redirections(t_arg *usrin);
void		set_out(t_cmd *cmd, t_arg **arg);
int			init_redirections(t_cmd *cmd);
void		split_expanded(char *usr_in, t_arg	**head);
int			open_heredoc(t_arg *target);
void		init_clear_argv(t_cmd *cmd);
void		data_init(char **base_env);
void		close_unused_fds(int next);
int			split_usrin(char *usr_in);
int			get_commands(t_arg *args);
int			get_argsc(char **args);
t_arg_type	is_io_op(char	*str);
char		*get_curr_path(int p);
int			check_qts(char *str);
int			is_valid_input(void);
void		set_io(t_cmd *cmd);
int			is_fod(char *name);
char		*get_prompt(void);

/**
 * FREE FREE FREEEEE :)
*/
void		child_proc_free(t_cmd *cmdptr, t_data *data);
void		free_tab(char **array);
void		_free(void);
void		restore(t_data *data);

#endif
