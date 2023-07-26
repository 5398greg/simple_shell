#include "main.h"
/**
 * prompt - Entry point
 * Description: 'we try'
 * @environ: 'environment variable'
 * Return: void
 */
void prompt(char **environ)
{
	char *string = NULL, *prompt = "$ ";
	int i, status;
	ssize_t numc_har;
	pid_t child_pid;

	size_t n = 0;
	char *argv[] = {NULL, NULL};

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);

		numc_har = getline(&string, &n, stdin);
		if (numc_har == -1)
		{
			error(string);
		}
		i = 0;
		while (string[i])
		{
			if (string[i] == '\n')
			string[i] = '\0';
			i++;
		}
		argv[0] = string;
		child_pid = fork();
		if (child_pid == -1)
		{
			error(string);
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				error(string);
			}
		} else
		wait(&status);
	}
}
