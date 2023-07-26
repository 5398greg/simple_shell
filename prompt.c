#include "main.h"
/**
 * prompt - Entry point
 * Description: 'display prompt'
 * @env: environment variable
 * Return: Always 0 (Success)
 */
void prompt(char **environ)
{
	char *prompt = "$ ", *cmdinput = NULL;
	size_t n;
	int i, status;
	pid_t bytes;
	char *arg[] = {NULL, NULL};

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		if (getline(&cmdinput, &n, stdin) == -1)
			error(cmdinput);
		i = 0;
		while (cmdinput[i])
		{
			if (cmdinput[i] == '\n')
				cmdinput[i] = '\0';
			i++;
		}
		arg[0] = cmdinput;
		bytes = fork();
		if (bytes == -1)
		{
			error(cmdinput);
		}
		else if (bytes == 0)
		if (execve(arg[0], arg, environ) == -1)
			error(cmdinput);
		wait(&status);
	}
}
