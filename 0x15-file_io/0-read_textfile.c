#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
	* read_textfile - reads and prints a text file to stdout
	* @filename: name of the file to read
	* @letters: number of letters to read and print
	* Return: actual number of letters read and printed, 0 on failure
*/
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t bytes_read, bytes_written;
	char *buffer;

	if (filename == NULL)
	return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	return (0);

	buffer = malloc(letters);
	if (buffer == NULL)
	{
	close(fd);
	return (0);
	}

	bytes_read = read(fd, buffer, letters);
	if (bytes_read == -1)
	{
	free(buffer);
	close(fd);
	return (0);
	}

	bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
	if (bytes_written == -1 || (size_t)bytes_written != (size_t)bytes_read)
	{
	free(buffer);
	close(fd);
	return (0);
	}

	free(buffer);
	close(fd);

	return (bytes_written);
}
