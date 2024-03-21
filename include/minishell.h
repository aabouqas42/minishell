/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/21 02:39:29 by aabouqas         ###   ########.fr       */
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
# include "dirent.h"

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
	t_env	*_env;
	char	**env;
	char	**argv;
	char	**paths;
	char	*prompt;
	char	*line;
	char	*program_path;
	int		exit_status;
}	t_data;

#define ENV_NOT_CREATED -1
#define ENV_FAILURE 0
#define ENV_CREATED 1

int		env_export(char *name, char *value, t_data *data);
t_env	*env_create(char *name, char *value);
t_env	*env_get(char *name, t_data	*data);
int		env_unset(char *name, t_env **env);
void	env_print_valueof(t_env *env);
t_env	*env_get_last(t_env	*env);
void	env_sort(t_env *env);
int		env_valid_name(char *name);
void	env_print(t_env	*head);
size_t	env_size(t_env *env);
void	env_free(t_env *env);
/*	END ENV LIST	*/


int		data_init(t_data *data, char **env);
int		is_valid_cmd(t_data *data, char *cmd);
void	_free(t_data *data);
void	free_tab(char **array);
char	*get_paths_env(t_data *data);
char	**_split(char *str, t_data *data);
char	*get_line(char *str);
char	*ft_strndup(char *str, size_t n);
char	*_strjoin(char *str1, char *str2);
void	ft_switcher(int *b, char *str, int size);
int		argument_count(char *str);
size_t	_strlen(char *str);

int		cd(char **argv);
void	echo(t_data *data);
int		pwd();


#endif
