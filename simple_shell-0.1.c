#include "shell.h"

/**
 * _getenv - Function to get the value of an environment variable
 * @name: The name of the environment variable
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
    extern char **environ;
    int i, len;

    if (!name || !environ)
        return (NULL);

    len = strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return (environ[i] + len + 1);
    }

    return (NULL);
}

/**
 * search_path - Function to search for the full path of a command
 * @command: The command to search for
 * Return: A struct stat_info containing the command and its full path,
 *         or NULL if the command is not found
 */
stat_info *search_path(char *command)
{
    char *path, *token, *temp;
    stat_info *info;
    struct stat st;

    path = _getenv("PATH");

    if (!path)
        return (NULL);

    temp = strdup(path);

    if (!temp)
        return (NULL);

    token = strtok(temp, ":");

    while (token)
    {
        info = malloc(sizeof(stat_info));
        if (!info)
        {
            free(temp);
            return (NULL);
        }

        info->path = malloc(strlen(token) + strlen(command) + 2);
        if (!info->path)
        {
            free(temp);
            free(info);
            return (NULL);
        }

        strcpy(info->path, token);
        strcat(info->path, "/");
        strcat(info->path, command);

        if (stat(info->path, &st) == 0)
        {
            info->command = strdup(command);
            free(temp);
            return (info);
        }

        free(info->path);
        free(info);
        token = strtok(NULL, ":");
    }

    free(temp);
    return (NULL);
}

/**
 * execute_command - Function to execute a command
 * @info: A struct stat_info containing the command and its full path
 * Return: 0 on success, -1 on failure
 */
int execute_command(stat_info *info)
{
    pid_t pid;
    int status;

    if (!info)
        return (-1);

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }

    if (pid == 0)
    {
	char *args[2];
        args[0] = info->command;
        args[1] = NULL;

        if (execve(info->path, args, NULL) == -1)
        {
            perror("execve");
            _exit(EXIT_FAILURE);
        }
    }
    else
    {
        do
        {
            if (waitpid(pid, &status, WUNTRACED) == -1)
            {
                perror("waitpid");
                return (-1);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (0);
}

/**
 * main - The main function for the shell
 * Return: Always 0
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    stat_info *info;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);

        characters = getline(&buffer, &bufsize, stdin);

        if (characters == -1)
        {
            if (feof(stdin))
            {
                write(STDOUT_FILENO, "\n", 1);
                free(buffer);
                exit(EXIT_SUCCESS);
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (characters > 1)
        {
            buffer[characters - 1] = '\0';

            info = search_path(buffer);

            if (!info)
            {
                write(STDERR_FILENO, "Command not found\n", 18);
            }
            else
            {
                execute_command(info);
                free(info->command);
                free(info->path);
                free(info);
            }
        }
    }

    return (0);
}

