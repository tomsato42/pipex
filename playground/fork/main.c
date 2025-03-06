#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;

	// Create a new process
	pid = fork();
	if (pid < 0)
	{
		// Fork failed
		perror("fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		// Child process
		printf("This is the child process. PID: %d\n", getpid());
	}
	else
	{
		// Parent process
		printf("This is the parent process. PID: %d\n", getpid());
		wait(NULL); // Wait for the child process to finish
		printf("Child process finished.\n");
	}
	return (0);
}
