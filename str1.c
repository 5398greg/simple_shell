#include "main.h"
/**
 * custom_strdup - Duplicate a string.
 * Description - 'behaves like strdup function'
 * @str: The string to be duplicated.
 *
 * Return: A pointer to a new string which is a duplicate of 'str',
 *         or NULL if 'str' is NULL or if memory allocation fails.
 */
char *custom_strdup(const char *str)
{
	char *duplicate;
	size_t len;

	if (str == NULL)
		return (NULL);

	len = custom_strlen(str);

	duplicate = (char *)malloc((len + 1) * sizeof(char));

	if (duplicate == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	custom_strcpy(duplicate, str, len + 1);
	return (duplicate);
}
/**
 * custom_strcpy - Copy a string from source to destination.
 * @dest: The destination buffer to copy the string to.
 * @src: The source string to be copied.
 * @dest_size: the size of dest
 * Return: A pointer to the destination buffer 'dest'.
 */
char *custom_strcpy(char *dest, const char *src, size_t dest_size)
{
	char *temp = dest;

	if (dest == NULL || src == NULL || dest_size == 0)
		return (NULL);

	while (*src && dest_size > 1)
	{
		*dest = *src;
		dest++;
		src++;
		dest_size--;
	}

	*dest = '\0';
	return (temp);
}
/**
 * custom_strcat - Concatenate two strings.
 * @dest: The destination buffer to concatenate the strings to.
 * @src: The source string to be concatenated.
 *
 * Return: A pointer to the destination buffer 'dest'.
 */
char *custom_strcat(char *dest, const char *src)
{
	char *temp = dest;

	if (dest == NULL || src == NULL)
		return (NULL);

	while (*dest)
		dest++;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (temp);
}
/**
 * custom_getenv_or_error - Get environment variable or print an error message.
 * @name: The name of the environment variable to get.
 *
 * Return: A pointer to the environment variable value, or NULL if not found.
 */
char *custom_getenv_or_error(const char *name)
{
	char *value = custom_getenv(name, environ);

	if (value == NULL)
	{
		perror(name);
		return (NULL);
	}
	return (value);
}

