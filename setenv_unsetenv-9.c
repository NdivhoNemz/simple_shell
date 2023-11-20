/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @var: The variable to set
 * @value: The value to set the variable to
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *var, const char *value)
{
	if (setenv(var, value, 1) == -1)
	{
		write(2, "Failed to set environment variable\n", 35);
		return (-1);
	}
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @var: The variable to unset
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *var)
{
	if (unsetenv(var) == -1)
	{
		write(2, "Failed to unset environment variable\n", 36);
		return (-1);
	}
	return (0);
}
