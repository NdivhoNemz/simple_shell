#include "shell.h"

/**
 * _getline - custom getline function
 * @fd: file descriptor
 * Return: line from stdin
 */
char *_getline(int fd)
{
	static char buffer[MAX_INPUT_SIZE];
	static char *ptr;
	static char *end;
	char *line;
	ssize_t n;

	if (ptr == end)
	{
		n = read(fd, buffer, MAX_INPUT_SIZE);
		if (n == 0)
			return (NULL);
		if (n < 0)
			return (NULL);
		ptr = buffer;
		end = buffer + n;
	}

	line = ptr;
	while (*ptr != '\n')
		ptr++;
	*ptr = '\0';
	ptr++;

	return (line);
}
