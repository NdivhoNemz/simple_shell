#include "shell.h"

/**
 * exit_built_in - A function that handles the exit built-in command
 * @args: The arguments for the exit command
 * Return: An integer status to exit the shell
 */
int exit_built_in(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
		if (status < 0)
		{
			write(2, "exit: Illegal number: ", 22);
			write(2, args[1], strlen(args[1]));
			write(2, "\n", 1);
			return (2);
		}
	}
	free(args);
	exit(status);
}
