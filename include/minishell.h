/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/04/30 11:52:46 by aabouqas         ###   ########.fr       */
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
#include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

# define P printf
# define ignore (void)

 
// dont forget to delete the following line :)
void	prt_tab(char **tab);
int		is_valid_input(char **usrin);
int		check_redirections(char **usrin);
void	expand_input(char **usrinput);
char	*skiper(char *str);
char	*_strchr(char *s, char c);
char	saver(char tosave);
// # define ERRT_SYNTAX "syntax error near unexpected token `"
// # define ERRT_COMDNF "command not found"

# define FILE 1
# define DIRE 2
typedef enum e_error_type{
	SYNTAX_ERR,
	COMDNF_ERR,
	ISDIR_ERR,
	NSFODIR_ERR,
	AMBIGUOUS_ERR,
	PERMIDEN_ERR
}	t_error_type;

void	do_error(t_error_type errtype, char *reason);

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


typedef enum e_flags
{
	FLAG_WORD,
	FLAG_IO_OP,
}	t_flags;

typedef struct s_data
{
	char	***cmds;
	t_env	*env;
	t_flags	*flags;
	char	**args;
	char	*prompt;
	char	*usrinput;
	char	*program_path;
	int		exit_status;
	char	*heredoc;
	int		in;
	int		out;
	int		oldfd;
	int		fds[2];
}	t_data;

char	**get_env_array();


char	*_strchr(char *s, char c);
int		env_export(char *name, char *value);
t_env	*env_create(char *name, char *value);
t_env	*env_get(char *name, t_data	*data);
int		env_unset(char *name, t_env **env);
t_env	*env_get_last(t_env	*env);
void	env_sort(t_env *env);
char	***get_commands();
int		cmds_counter(char **cmds);
void	data_init(char **base_env);
void	init_default_envs();
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
int		check_input(char **cmds);

int		is_valid_cmd(t_data *data, char *cmd);
void	safe_exit(int status);
void	free_tab(char **array);
void	split_usrin(char *usr_in);
char	*_strjoin(char *str1, char *str2);
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
int		_spaces(int c);
int		request_input();
char	*remove_qts(char *str);
int		set_var(char *argv_str, char **str);
int		check_quotes_closed(char *str);
char	**_realloc(char **old_tab, char *to_append);

void	open_heredoc(char *target);
void	set_out(char **arg);
void	set_in_out();
char	**get_argv(char **args);
void	set_pipes(int first, int there_is_next);

char	*ft_strtokenize(char *src, char c);

#endif
