#include <stdio.h>

int main(int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		printf("[%s]\n", av[i]);
		i++;
	}
	return (0);
}