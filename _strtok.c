#include "shell.h"

/**
 * count_tokens - Count the number of tokens in a string
 * @str: The string to count tokens in
 * @delim: The delimiter to use for tokenization
 * Return: The number of tokens
 */
int count_tokens(const char *str, const char *delim) {
    int count = 0;
    while (*str != '\0') {
        str = skip_delim(str, delim);
        if (*str == '\0') {
            break;
        }
        count++;
        str += get_token_length(str, delim);
    }
    return count;
}

/**
 * skip_delim - Move the string pointer past leading delimiters
 * @str: The string to process
 * @delim: The delimiter characters
 * Return: A pointer to the first non-delimiter character
 */
const char *skip_delim(const char *str, const char *delim) {
    while (*str != '\0' && strchr(delim, *str) != NULL) {
        str++;
    }
    return str;
}

/**
 * get_token_length - Get the length of the next token in a string
 * @str: The string to process
 * @delim: The delimiter characters
 * Return: The length of the token
 */
int get_token_length(const char *str, const char *delim) {
    int length = 0;
    while (*str != '\0' && strchr(delim, *str) == NULL) {
        length++;
        str++;
    }
    return length;
}

/**
 * allocate_token - Allocate memory for a token and copy it
 * @str: The string containing the token
 * @length: The length of the token
 * Return: A pointer to the allocated token
 */
char *allocate_token(const char *str, int length) {
    char *token = malloc(length + 1);
    if (token == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(token, str, length);
    token[length] = '\0';
    return token;
}

/**
 * free_tokens - Free memory allocated for an array of tokens
 * @tokens: The array of tokens
 * @count: The number of tokens in the array
 */
void free_tokens(char **tokens, int count) {
	int i;
    for (i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
