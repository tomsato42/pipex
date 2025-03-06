#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid = fork();

	if (pid == -1) {
		 
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		// Child process
		printf("Child process (PID: %d) is running...\n", getpid());
		sleep(2); // Simulate some work in the child process
		printf("Child process (PID: %d) is exiting...\n", getpid());
		exit(EXIT_SUCCESS);
	} else {
		// Parent process
		int status;
		pid_t waited_pid = waitpid(pid, &status, 0);

		if (waited_pid == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status)) {
			printf("Child process (PID: %d) exited with status %d\n", waited_pid, WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("Child process (PID: %d) was terminated by signal %d\n", waited_pid, WTERMSIG(status));
		} else {
			printf("Child process (PID: %d) ended unexpectedly\n", waited_pid);
		}
	}

	return 0;
}
