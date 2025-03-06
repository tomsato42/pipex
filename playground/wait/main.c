#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid = fork();

	if (pid < 0) {
		perror("fork failed");
		return 1;
	}

	if (pid == 0) {
		// Child process
		printf("Child process (PID: %d)\n", getpid());
		sleep(2); // Simulate some work in the child process
		exit(0);
	} else {
		// Parent process
		printf("Parent process (PID: %d) waiting for child process (PID: %d)\n", getpid(), pid);
		int status;
		wait(&status); // Wait for the child process to finish
		if (WIFEXITED(status)) {
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		} else {
			printf("Child process did not exit normally\n");
		}
	}

	return 0;
}
