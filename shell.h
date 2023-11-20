#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/* for read/write buffers */
#define MAX_INPUT_SIZE 1024

/**
 * struct info_s - Struct to hold shell info
 * @data: The data of the shell
 */
typedef struct info_s
{
    char *data;
} info_t;

/* Shell utility functions */

/* exits shell and tokenize string*/
int exit_shell(info_t *info);
char **_strtok(char *str, const char *delim);

/* handles line and current environment*/
void print_env(char **env);
char *_getline(int fd);

/* handles path and execute commands*/
int handle_path(char **args);
int execute_command(char *args[]);

/* handles setenv & unsetenv*/
int _setenv(const char *var, const char *value);
int _unsetenv(const char *var);

#endif /* SHELL_H */
