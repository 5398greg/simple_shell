#include "main.h"
/**
 * prompt - Entry point
 * Description: 'we try'
 * @environ: 'environment variable'
 * @argv: 'arguement vector'
 * Return: void
 */
void prompt(char **environ, char argv[])
{
	char *string = NULL, *prompt = "#cisfun$ ";
	int i, status;
	ssize_t numc_har;
	pid_t child_pid;

	size_t n = 0;
	char *argv1[] = {NULL, NULL};

	while (1)
	{
		/*if (isatty(STDIN_FILENO))*/
		write(STDOUT_FILENO, prompt, 2);

		numc_har = getline(&string, &n, stdin);
		if (numc_har == -1)
		{
			error(string, argv);
		}
		i = 0;
		while (string[i])
		{
			if (string[i] == '\n')
			string[i] = '\0';
			i++;
		}
		argv1[0] = string;
		child_pid = fork();
		if (child_pid == -1)
		{
			error(string, argv);
		}
		if (child_pid == 0)
		{
			if (execve(argv1[0], argv1, environ) == -1)
			{
				error(string, argv);
			}
		}
		if (child_pid > 0)
			wait(&status);
	}
	free(string);
}
