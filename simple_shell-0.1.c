#include "shell.h"

/**
 * execute_command - Forks a process and executes a command
 * @args: Array of command-line arguments
 */
void execute_command(char *args[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, NULL, 0);
	}
}

/**
 * main - Simple UNIX command line interpreter
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	while (1)
	{
		char **args;

		/* Display the shell prompt */
		if (write(STDOUT_FILENO, "$ ", 2) == -1)
		{
			perror("write");
			break;
		}

		if (getline(&input, &input_size, stdin) == -1)
		{
			perror("getline");
			break; /* Exit on EOF (Ctrl+D) */
		}

		/* Remove newline character */
		input[strcspn(input, "\n")] = '\0';

		/* Tokenize the input into arguments */
		args = _strtok(input, " ");
		if (args == NULL)
		{
			fprintf(stderr, "Error: Failed to tokenize input\n");
			break;
		}

		/* Execute the command */
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free(args); /* Free memory allocated for arguments */
				break;      /* Exit the shell */
			}
			else
			{
				execute_command(args);
			}
		}

		free(args); /* Free memory allocated for arguments */
	}

	/* Free dynamically allocated memory */
	free(input);

	return 0;
}
