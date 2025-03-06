#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0) {
		perror("open");
		return 1;
	}

	// Duplicate file_fd to stdout (file descriptor 1)
	if (dup2(file_fd, STDOUT_FILENO) < 0) {
		perror("dup2");
		close(file_fd);
		return 1;
	}

	// Now stdout is redirected to output.txt
	printf("This will be written to output.txt\n");

	close(file_fd);
	return 0;
}
