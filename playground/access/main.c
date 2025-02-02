#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/*
 Function: Check if the file is executable.
 Arguments: File path
 Return value:
 0 -> Executable
 -1 -> Not executable
*/

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK))
	{
		printf("returns %d\n", access(argv[1], R_OK | X_OK ));
		printf("File does not exitst:%s\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK | X_OK ) == 0)
	{
		printf("returns %d\n", access(argv[1], R_OK | X_OK ));
		printf("Excutable file:%s\n",argv[1]);
	}
	else
	{
		printf("returns %d\n", access(argv[1], R_OK | X_OK ));
		printf("Parmission Deny:%s\n",argv[1]);
	}
	return (0);
}
