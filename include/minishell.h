/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/09 21:13:58 by aabouqas         ###   ########.fr       */
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
	NOTDIRECTORY_ERR
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
	struct termios	*old_termios;
	struct termios	*curr_termios;
	t_cmd			*cmds;
	t_env			*env;
	t_arg			*args;
	char			**env_2d;
	char			*prompt;
	char			*usrinput;
	char			*program_path;
	int				exit_status;
	int				oldfd;
	int				fix_doubleprt;
	int				fds[2];
}	t_data;

/**
 * T_ARG INSTRACTIONS
 */
void		t_arg_insert(char *value, t_arg_type type, t_arg **head);
void		t_arg_put(char *value, t_arg_type type, t_arg **head);
void		t_arg_add(char *value, t_arg_type type);
void		t_arg_free(t_arg *head);

/**
 * T_CMD INSTRACTIONS
 */
void		t_cmd_add(t_cmd to_add);
void		t_cmd_free(t_cmd *head);

/**
 * SIGNALS FUNCTIONS
 */
void		catch_signals(void);
void		sig_handle_sigquit(int sig);
void		sig_handle_sigint(int sig);

int			open_heredoc(t_arg *target);
t_data		*data_hook(t_data *data);

void		init_redirections(t_cmd *cmd);
void		init_clear_argv(t_cmd *cmd);

void		do_error(t_error_type errtype, char *reason);
t_env		*env_create(char *name, char *value);
t_env		*env_get(char *name, t_data	*data);
t_env		*env_get_last(t_env	*env);
size_t		env_size(t_env *env);
void		init_env_array(void);
char		*env_grepvalue(char *name);
int			env_unset(char *name, t_env **env);
int			env_export(char *name, char *value);
int			env_valid_name(char *name);
void		env_print(t_env	*head);
void		env_sort(t_env *env);
void		get_commands(t_arg *args);
void		data_init(char **base_env);
char		*get_prompt(void);
char		*get_curr_path(void);
t_arg_type	is_io_op(char	*str);
void		free_tab(char **array);
void		_free(void);
void		env_free(t_env *env);
void		env_free_list(t_env *env);
size_t		_strlenc(char *str, char c);
size_t		_strlen(char *str);
char		*_strjoin(char *str1, char *str2);
char		*_strnjoin(char *str1, char *str2, size_t size);
char		*_strdup(char *s1);
char		*_strndup(char *s1, size_t size);
char		*_strchr(char *s, char c);
int			is_valid_cmd(t_data *data, char *cmd);
void		safe_exit(int status);
void		split_usrin(char *usr_in);
int			is_same(char *s1, char *s2);
int			builtins(t_cmd *cmd);
int			cd(char **argv);
int			pwd(void);
int			_export(char **argv);
int			run_builtin(t_cmd *cmd);
void		echo(char **argv);
char		**_realloc(char **old_tab, char *to_append);
void		*_calloc(size_t size);
int			_spaces(int c);
int			set_var(char *argv_str, char **str);
int			check_qts(char *str);
int			is_fod(char *name);
void		set_out(t_cmd *cmd, t_arg **arg);
void		set_io(t_cmd *cmd);
void		set_pipes(t_cmd *cmd, int first, int next);
int			is_valid_input(void);
int			check_redirections(t_arg *usrin);
char		*skiper(char *str);
char		*_strchr(char *s, char c);
int			get_argsc(char **args);
void		print(int fd, char *str, int endl);
int			is_builtin(t_cmd *cmd);
void		prt_list(t_arg *arg); // REMOVE BFR PUSH
char		*expand_arg(char *str, int hd, int rm_qts);
void		split_expanded(char *usr_in);
t_arg		*get_last(t_arg *head);
int			var_case(char curr_char, char next_char);
void		check_arguments(int ac, char **av);
#endif
