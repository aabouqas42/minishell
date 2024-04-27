#include "include/minishell.h"

void	prt_tab(char **tab)
{
	int	i = 0;

	if (tab == NULL)
	{
		printf("---EMPTY---\n");
		return ;
	}
	while (tab[i])
	{
		printf("[%s]\n", tab[i]);
		i++;
	}
}
