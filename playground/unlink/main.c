#include <stdio.h>
#include <unistd.h>

int main() {
	const char *filename = "testfile.txt";

	// Create a file
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		perror("Failed to create file");
		return 1;
	}
	fprintf(file, "This is a test file.\n");
	fclose(file);

	// Unlink (delete) the file
	if (unlink(filename) == 0) {
		printf("File '%s' deleted successfully.\n", filename);
	} else {
		perror("Failed to delete file");
		return 1;
	}

	return 0;
}
