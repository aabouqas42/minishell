/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:22:49 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/16 03:05:41 by mait-elk         ###   ########.fr       */
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

int		env_add(char *name, char *value, t_env **env);
void	env_print(t_env	*head);
/*	END ENV LIST	*/

typedef struct s_data
{
	char	**env;
	char	**argv;
	char	**paths;
	char	*promte;
	char	*line;
	char	*program_path;
}	t_data;


int		is_valid_cmd(t_data *data, char *cmd);
int		data_init(t_data *data, char **env);
void	_free(t_data *data);
void	free_tab(char **array);
char	*get_paths_env(t_data *data);
int		cd(char *dir_name);
int		echo(char *args);
int		pwd();

char	**_split(char *line, char c);
size_t	word_counter(char *rdline);

int	wc(char *s);
#endif
