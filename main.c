#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	closer(int fds[][2], int size)
{
	int i = 0;
	while (i < size)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int	fds[argc - 1][2];

	int i = 0;
	while (i < argc - 1)
		pipe(fds[i++]);
	i = 1;
	int size = argc - 1;
	int j = 0;
	while (i < argc)
	{
		int child = fork();
		if (child == 0)
		{
			if (i == 1 && argv[i + 1] != NULL)
			{
				dup2(fds[j][1], 1);
			} else if (i != 1 && argv[i + 1] != NULL)
			{
				dup2(fds[j][0], 0);
				dup2(fds[j + 1][1], 1);
			} else if (i != 1 && argv[i + 1] == NULL)
			{
				dup2(fds[j][0], 0);
			}
			if (size > 1)
				closer(fds, size);
			system(argv[i]);
			exit(0);
		}
		j++;
		i++;
	}
	// int c1 = fork();
	// if (c1 == 0)
	// {
	// 	dup2(fds[0][1], STDOUT_FILENO);
	// 	i = 0;
	// 	closer(fds, 3);
	// 	system(argv[1]);
	// 	exit(0);
	// }
	// int c2 = fork();
	// if (c2 == 0)
	// {
	// 	dup2(fds[0][0], STDIN_FILENO);
	// 	dup2(fds[1][1], STDOUT_FILENO);
	// 	closer(fds, 3);
	// 	system(argv[2]);
	// 	exit(0);
	// }
	// int c3 = fork();
	// if (c3 == 0)
	// {
	// 	dup2(fds[1][0], STDIN_FILENO);
	// 	closer(fds, 3);
	// 	system(argv[3]);
	// 	exit(0);
	// }
	closer(fds, size);
	while (wait(0) != -1);
	while(1);
	return (0);
}