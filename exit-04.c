#include "shell.h"
#include <stdlib.h>

/**
 * exit_shell - Exits the shell
 * @info: Shell info
 * Return: 0 on success, -1 on failure
 */
int exit_shell(info_t *info)
{
    /* Free the allocated memory before exiting */
	free(info->data);
	free(info);
return (0);
}
