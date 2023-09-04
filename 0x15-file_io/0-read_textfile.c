#include "main.h"
#include <stdlib.h>

/**
	* custom_read_and_print - Read text file and print to STDOUT.
	* @filename: The name of the text file to be read.
	* @letters: The number of letters to be read and printed.
	*
	* Return: The actual number of bytes read and printed, or 0 on failure.
*/
ssize_t custom_read_and_print(const char *filename, size_t letters)
	{
	char *custom_buffer;
	ssize_t custom_fd;
	ssize_t custom_bytes_read;
	ssize_t custom_bytes_written;

	custom_fd = open(filename, O_RDONLY);
	if (custom_fd == -1)
	return (0);

	custom_buffer = malloc(sizeof(char) * letters);
	if (custom_buffer == NULL)
	{
	close(custom_fd);
	return (0);
	}

	custom_bytes_read = read(custom_fd, custom_buffer, letters);
	if (custom_bytes_read == -1)
	{
	free(custom_buffer);
	close(custom_fd);
	return (0);
	}

	custom_bytes_written = write(STDOUT_FILENO, custom_buffer, custom_bytes_read);

	free(custom_buffer);
	close(custom_fd);

	if (custom_bytes_written == -1 || custom_bytes_written != custom_bytes_read)
	{
	return (0);
	}

	return (custom_bytes_written);
}
