#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *s = "ls \"-la ewe\" | grep Makefile";
	char	**argv = calloc (6, sizeof(char *));
	int i = 0;
	while (*s)
	{
	}
}
