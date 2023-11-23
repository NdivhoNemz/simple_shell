#include "shell.h"

/**
 * handle_arg - Forks a process and executes a command
 * @args: Array of command-line arguments
 */
void handle_arg(char *args[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Failed to execute command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		if (wait(&status) == -1)
		{
			perror("Failed to wait");
			exit(EXIT_FAILURE);
		}
	}
}
