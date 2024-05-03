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