#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	pid_t	cpid;
	char	buf;

	int pipefd[2]; // 0が読み取り用、1が書き込み用
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("pipefd 0:%d,1:%d\n", pipefd[0], pipefd[1]);
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{ // Child process
		printf("cpid : %d\n", cpid);
		close(pipefd[1]); // Close unused write end
		while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	}
	else
	{ // Parent process
		printf("child process id : %d\n", cpid);
		close(pipefd[0]); // Close unused read end
		write(pipefd[1], "Hello, world!\n", 14);
		close(pipefd[1]); // Reader will see EOF
		wait(NULL);       // Wait for child
		exit(EXIT_SUCCESS);
	}
}
