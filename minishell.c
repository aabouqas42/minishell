#include "minishell.h"

int main(int ac, char **av, char **env)
{
	while (1)
	{
		char *line = readline(">> ");
		printf("\n[%s]\n", line);
		free (line);
	}
}
