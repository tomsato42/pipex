#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int	open_non_exitstent_file()
{
	int a;
	a = open("non_existent_file.txt", O_RDONLY);
	if (a == -1)
	{
		perror("Error");
		exit(1);
	}
	close(a);
	return (0);
}

int main()
{
	open_non_exitstent_file();
	return (0);
}
