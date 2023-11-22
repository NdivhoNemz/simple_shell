#include "shell.h"

/**
 * cd - Changes the current directory of the process
 * @args: The command line arguments
 * Return: 1 if successful, -1 if fail
 */
int cd(char **args)
{
	char *home = getenv("HOME");
	char *oldpwd = getenv("OLDPWD");
	char *newpwd = NULL;

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		if (chdir(home) != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (chdir(oldpwd) != 0)
		{
			perror("cd");
			return (-1);
		}
		write(1, oldpwd, strlen(oldpwd));
		write(1, "\n", 1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (-1);
		}
	}

	newpwd = getcwd(NULL, 0);
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", newpwd, 1);
	free(newpwd);

	return (1);
}
