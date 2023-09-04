#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 1024

/**
	* main - program that copies the content of a file to another file
	* @argc: number of arguments
	* @argv: array of arguments
	* Return: 0 on success, appropriate exit code on failure
*/
int main(int argc, char *argv[])
{
	int fd_from, fd_to, close_result;
	char buffer[BUF_SIZE];
	ssize_t bytes_read = 0, bytes_written = 0;

	if (argc != 3)
	{
	dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
	return (97);
	}

	fd_from = open(argv[1], O_RDONLY);

	if (fd_from == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
	return (98);
	}

	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	if (fd_to == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
	close(fd_from);
	return (99);
	}

	while ((bytes_read = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
	bytes_written = write(fd_to, buffer, bytes_read);

	if (bytes_written == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
	close(fd_from);
	close(fd_to);
	return (99);
	}
	}

	if (bytes_read == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
	close(fd_from);
	close(fd_to);
	return (98);
	}

	close_result = close(fd_from);

	if (close_result == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
	return (100);
	}

	close_result = close(fd_to);

	if (close_result == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
	return (100);
	}

	return (0);
}
