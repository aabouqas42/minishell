#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char bffer[5];
	int fwrite = open("file", O_CREAT | O_RDWR, 0x777);
	int fread = open("file", O_RDONLY);
	unlink("file");
	// printf("%d\n", );
	printf("%d - %d\n", fwrite, fread);
	write(fwrite, "hello", 10);

	int fwrite2 = open("file", O_CREAT | O_RDWR, 0x777);
	int fread2 = open("file", O_RDONLY);
	unlink("file");
	// printf("%d\n", );
	printf("%d - %d\n", fwrite2, fread2);e
	write(fwrite2, "\n", 1);
	while(1);
}