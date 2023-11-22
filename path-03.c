#include "shell.h"


#define MAX_INPUT_SIZE 1024

/**
 * handle_path - Handles the PATH
 * @args: Array of command-line arguments
 * Return: 0 on success, -1 on failure
 */
int handle_path(char **args)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char *cmd_path = malloc(MAX_INPUT_SIZE);

	if (!cmd_path)
	{
		perror("Error: ");
		return (-1);
	}

	while (token)
	{
		cmd_path[0] = '\0';
		strcat(cmd_path, token);
		strcat(cmd_path, "/");
		strcat(cmd_path, args[0]);

		if (access(cmd_path, X_OK) == 0)
		{
			args[0] = cmd_path;
			return (0);
		}
		token = strtok(NULL, ":");
	}
	free(cmd_path);
	return (-1);
}

/**
 * exec_command - Forks a process and executes a command
 * @args: Array of command-line arguments
 * Return: 0 on success, -1 on failure
 */
int exec_command(char *args[])
{
	pid_t pid;
	int status;

	if (handle_path(args) == -1)
	{
		write(2, "Command not found\n", 18);
		return (-1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error: ");
		return (-1);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}
