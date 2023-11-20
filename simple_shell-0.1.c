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
		/* Display the shell prompt */
		write(STDOUT_FILENO, "$ ", 2);
		if (getline(&input, &input_size, stdin) == -1)
		{
			break; /* Exit on EOF (Ctrl+D) */
		}
		/* Remove newline character */
		input[strcspn(input, "\n")] = '\0';
		/* Tokenize the input into arguments */
		char *token;
		char *args[20]; /* Maximum number of arguments */
		int i = 0;

		token = strtok(input, " ");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL; /* Null-terminate the argument list */
		/* Execute the command */
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				break; /* Exit the shell */
			}
			else
			{
				execute_command(args);
			}
		}
	}
	free(input);
return (0);
}
