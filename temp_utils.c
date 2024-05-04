/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:16:07 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/04 12:10:52 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	prt_tab(char **tab)
{
	int	i;

	if (tab == NULL)
	{
		printf("---EMPTY---\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		printf("[%s]\n", tab[i]);
		i++;
	}
}
void print_open_file_descriptors()
{
   int fd;
    char path[256];
    
    for(fd = 0; fd < 2500; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            if (fcntl(fd, F_GETPATH, path) != -1) {
                dprintf(2,"File descriptor %d is referencing: %s\n", fd, path);
            } else {
                dprintf(2,"File descriptor %d is not associated with an open file.\n", fd);
            }
        }
    }
}

 // from export :)
	// if (i == 0)
	// 	return (env_sort(data->env), 0);

	// name = data->args[1];
	// value = "";
	// i = 0;
	// if (ft_strchr(name, '='))

	// while (name[i] && name[i] != '=')
	// 	i++;
	// if (name[i] == '=')
	// 	value = (name + i + 1);
	// name[i] = '\0';
	// if (env_export(name, value))
	// 	return (1);
	// return (
	//printf(// "minishell: export: `%s=%s': not a valid identifier\n", name, value)
	// , 0);
