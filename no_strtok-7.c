#include "shell.h"

/**
 * _strtok - A function that tokenizes a string
 * @str: The string to tokenize
 * @delim: The delimiter to tokenize by
 * Return: An array of tokens
 */
char **_strtok(char *str, const char *delim)
{
	int i, j;
	int token_count = 0;
	char **tokens;

	token_count = count_tokens(str, delim);

	tokens = malloc(sizeof(char *) * (token_count + 2));
	if (tokens == NULL)
	{
		write(STDOUT_FILENO, "Error: Failed to allocate memory for tokens\n", 44);
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (*str != '\0')
	{
		const char *temp_str = skip_delim(str, delim); /* temp_str as const */
		if (*temp_str == '\0')
			break;

		j = get_token_length(str, delim);

		tokens[i] = allocate_token(str, j);
		if (tokens[i] == NULL)
		{
			free_tokens(tokens, i);
			write(STDOUT_FILENO, "Error: Failed to allocate memory for a token\n", 45);
			exit(EXIT_FAILURE);
		}

		str += j;
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}
