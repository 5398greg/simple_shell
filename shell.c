#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 1024

int main(int argc, char *argv[], char *envp[])
{
	char *prompt = "$ ";
	char *buff = NULL;
	size_t n = 0;
	int bytes;
	bool frompipe = false;

	while (!frompipe)
	{
		if (isatty(STDIN_FILENO) == 0)
		frompipe = true;

		write(STDOUT_FILENO, prompt, 2);

		bytes = getline(&buff, &n, stdin);
		if (bytes == -1)
		{
			perror("Getline error\n");
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';

		char *delim = " \n";
		char *token = strtok(buff, delim);
		int i = 0;
		char *tokens[MAX];

		while (token != NULL)
		{
			tokens[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		tokens[i] = NULL;
		pid_t pid = fork();

		if (pid == -1)
		{
			free(buff);
			perror("Error (Fork)\n");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			int val = execve(tokens[0], tokens, NULL);

			if (val == -1)
			{
				free(buff);
				perror("Error (Execve)\n");
				exit(EXIT_FAILURE);
			}
		} else
		{

			int status;

			wait(&status);
		}
		}

	free(buff);
	return (0);
}

