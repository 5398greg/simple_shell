#include "main.h"
/**
 * read_input - Entry point
 * Description: 'to read input and know whether its piped'
 * @is_interactive: just an integer pointer
 * Return: string
 */
char *read_input(int *is_interactive)
{
	char *string = NULL;
	size_t n = 0;
	ssize_t numc_har;

	*is_interactive = isatty(STDIN_FILENO);

	if (*is_interactive)
	{
		write(STDOUT_FILENO, "$ ", 2);
		numc_har = getline(&string, &n, stdin);
	} else
	{
		numc_har = getline(&string, &n, stdin);
	}

	if (numc_har == -1)
	{
		perror("getline");
		free(string);
		string = NULL;
	} else
	{
		string[numc_har - 1] = '\0';
	}

	return (string);
}
/**
 * execute_command - Entry point
 * Description: 'executes the command with execve'
 * @command: command entered
 * @environ: external variables
 * Return: void
 */
void execute_command(char *command, char **environ)
{
	char **argv1 = malloc(2 * (sizeof(char *)));
	pid_t child_pid;
	int status;

	if (argv1 == NULL)
	{
		perror("malloc");
		free(command);
		exit(EXIT_FAILURE);
	}
	argv1[0] = command;
	argv1[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(argv1);
		free(command);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(command, argv1, environ) == -1)
		{
			perror("execve");
			free(argv1);
			free(command);
			exit(EXIT_FAILURE);
		}
	} else
	{
		wait(&status);
	}
	free(argv1);
	free(command);
}
/**
 * prompt - Entry point
 * Description: 'runs the prompt'
 * @environ: exernal environment variable
 * Return: void
 */
void prompt(char **environ)
{
	while (1)
	{
		int is_interactive;
		char *command = read_input(&is_interactive);

		if (command == NULL)
		{
			break;
		}

	if (is_interactive && command[0] != '\0')
	{
		execute_command(command, environ);
	}
	}
}

