#include "main.h"
/**
 * is_absolute - Entry point
 * Description: 'to check if it is absolute or relative'
 * @check: command to be checked
 * Return: Always 0 (Success)
 */
int is_absolute(char *check)
{
	if (check == NULL || check[0] != '/')
		return (0);
	return (1);
}
/**
 * exec_absolute - Entry point
 * Description: 'execute the path'
 * @string: the absolute path
 * @environ: environment variable
 * Return: void
 */
void exec_absolute(char *string, char **environ)
{
	int status;
	pid_t pid;
	ssize_t numc_har;
	char **args = tokenize_input(string);

	numc_har = custom_strlen(string);
	if (string[numc_har - 1] == '\n')
		string[numc_har - 1] = '\0';

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(string, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &status, 0);
}
