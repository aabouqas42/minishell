#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "include/minishell.h"

int	main(int argc, char **argv)
{
    int fds[2];
    int fds2[2];
    pipe(fds);
    if (fork() == 0)
    {
        dup2(fds[1], 1);
        close(fds[0]);
        close(fds[1]);
        char	**arg = NULL;
        arg = _realloc(arg, "ls");
        execve("/bin/ls", arg, NULL);
    }
    pipe(fds2);
    if (fork() == 0)
    {
        dup2(fds[0], 0);
        close(fds[0]);
        close(fds[1]);
        dup2(fds2[1], 1);
        close(fds2[0]);
        close(fds2[1]);
        char *argv[] = {"grep", "m", NULL};
        execve("/usr/bin/grep", argv, NULL);
    }
    close(fds[0]);
    close(fds[1]);
    if (fork() == 0)
    {
        dup2(fds2[0], 0);
        close(fds2[0]);
        close(fds2[1]);
        char *argv[] = {"wc", "-l", NULL};
        execve("/usr/bin/wc", argv, NULL);
    }
    close(fds2[0]);
    close(fds2[1]);
    wait(NULL);
}