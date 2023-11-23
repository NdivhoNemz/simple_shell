#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

char *_getenv(const char *name);
typedef struct stat_info
{
    char *command;
    char *path;
} stat_info;

stat_info *search_path(char *command);
int execute_command(stat_info *info);

#endif /* SHELL_H */
