#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	buffer[30];

	// Create a pipe
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// Fork a child process
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{ // Child process
		// Close the read end of the pipe
		close(pipefd[0]);
		// Close stdout
		close(STDOUT_FILENO);
		// Duplicate the write end of the pipe to stdout
		dup(pipefd[1]);
		// Write to stdout (which is now the write end of the pipe)
		printf("Hello from child process!\n");
		// Close the write end of the pipe
		close(pipefd[1]);
	}
	else
	{ // Parent process
		// Close the write end of the pipe
		close(pipefd[1]);
		// Read from the read end of the pipe
		int n = read(pipefd[0], buffer, sizeof(buffer) - 1);  // 1バイト少なく読み込む
		buffer[n] = '\0';  // 手動でNULL終端を追加
		// Print the message from the child process
		printf("Parent received: %s", buffer);
		// Close the read end of the pipe
		close(pipefd[0]);
	}
	return (0);
}
