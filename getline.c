#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of len variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t buffer_len = 0;

	if (!*len) /* If nothing left in the buffer, fill it. */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		bytes_read = getline(buf, &buffer_len, stdin);
#else
		bytes_read = _getline(info, buf, &buffer_len);
#endif

		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0'; /* Remove trailing newline. */
				bytes_read--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			/* Check if it's a command chain. */
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *cmd_chain_buf; /* The ';' command chain buffer. */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &cmd_chain_buf, &len);

	if (bytes_read == -1) /* EOF */
		return (-1);

	if (len) /* Commands left in the chain buffer. */
	{
		j = i;
		p = cmd_chain_buf + i;

		check_chain(info, cmd_chain_buf, &j, i, len);

		while (j < len)
		{
			if (is_chain(info, cmd_chain_buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = cmd_chain_buf;
	return (bytes_read);
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: Bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);

	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);

	if (bytes_read >= 0)
		*i = bytes_read;

	return (bytes_read);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Size.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;

	if (i == len)
		i = len = 0;

	bytes_read = read_buf(info, buf, &len);

	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (size)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = size;

	*ptr = p;
	return (size);
}

/**
 * sigintHandler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
