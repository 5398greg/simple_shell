#include "main.h"
/**
 * custom_strcmp - Entry point
 * Description: 'compares two strings'
 * @str1: string to compare
 * @str2: string to compare
 * Return: Always 0 (Success)
 */
int custom_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
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
	int fd = fileno(stdin);

	*is_interactive = isatty(fd);

	if (*is_interactive)
	{
		write(STDOUT_FILENO, "$ ", 2);
		numc_har = getline(&string, &n, stdin);
	} else
		return (NULL);

	if (numc_har == -1)
	{
		perror("getline");
		free(string);
		string = NULL;
	}
	if (string[numc_har - 1] == '\n')
		string[numc_har - 1] = '\0';

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
	char **args = NULL, *full_path = NULL;
	int status;
	pid_t child_pid;

	args = tokenize_input(command);
	if (args == NULL)
		return;

	if (is_builtin(args[0]))
	{
		handle_builtin(args[0]);
		free_args(args);
		return;
	}
	full_path = find_full_path(args[0]);

	if (full_path == NULL)
	{
		perror(args[0]);
		free_args(args);
		return;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(full_path), free(args);
		return;
	}
	if (child_pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
		waitpid(child_pid, &status, 0);
	free(full_path);
	free_args(args);
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
		char *command = NULL;

		command = read_input(&is_interactive);
		if (command == NULL)
			continue;
		if (is_interactive && command[0] != '\0')
		{
			if (custom_strcmp(command, "exit") == 0)
			{
				free(command);
				break;
			}

			execute_command(command, environ);
		}
		free(command);
	}
}
