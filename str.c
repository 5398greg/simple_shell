#include "main.h"
/**
 * custom_getenv - Entry point
 * Description: 'searches for name in environment variables'
 * @environ: environment variable
 * @name: the name to be checked
 * Return: Always something (Success)
 */
char *custom_getenv(const char *name, char **environ)
{
	size_t nameLen;
	char **env;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}

	nameLen = custom_strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (custom_strncmp(name, *env, nameLen) == 0 && (*env)[nameLen] == '=')
		{
			return (*env + nameLen + 1);
		}
	}

	return (NULL);
}
/**
 * custom_strlen - Calculate the length of a string.
 * @str: The input string.
 * Return: The length of the string.
 */
unsigned int custom_strlen(const char *str)
{
	unsigned int length = 0;

	if (str == NULL)
		return (0);

	while (*str)
	{
		length++;
		str++;
	}

	return (length);
}
/**
 * custom_strncmp - Compare two strings up to a given number of characters.
 * @str1: The first input string.
 * @str2: The second input string.
 * @n: The maximum number of characters to compare.
 *
 * Return:
 *   0 if the strings are equal up to 'n' characters.
 */
int custom_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);

	for (i = 0; i < n - 1; i++)
	{
		if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
			return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
	}

	return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
}
