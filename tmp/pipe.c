#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "include/minishell.h"

int main(int ac, char **av) {
	int in = dup(0);
    int fd[2];

	pipe(fd);
	int pid = fork();
	if (pid == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char **av = ft_split("ls -l", ' ');
		execve("/bin/ls", av, NULL);
	}

	dup2(fd[0], 0);
	pid = fork();
    if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
		char **av = ft_split("grep mait", ' ');
        execve("/usr/bin/grep", av, NULL);
    }
    close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	pipe(fd);
	pid = fork();
    if (pid == 0) {
        close(fd[0]);
        close(fd[1]);
		char **av = ft_split("grep 102", ' ');
        execve("/usr/bin/grep", av, NULL);
    }
	dup2(in ,0);
	close(in);
    close(fd[0]);
    close(fd[1]);
    waitpid(-1, NULL, 0);
    return 0;
}