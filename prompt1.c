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
		fprintf(stderr, "%s: command not found\n", args[0]);
		free_args(args);
		return;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(full_path), free_args(args);
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
 * prompt - a normal function
 * @environ: exernal environment variable
 * Return: void
 */
void prompt(char **environ, bool frompipe)
{
	while (!frompipe)
	{
		char *string = NULL;
		size_t n = 0;
		ssize_t numc_har;
		int fd = fileno(stdin);

		if (isatty(fd) == 1)
		{
			write(STDOUT_FILENO, "$ ", 2);
			numc_har = getline(&string, &n, stdin);
		} else
			frompipe = true;
		if (numc_har == -1)
		{
			perror("getline");
			free(string);
			string = NULL;
		}
		if (is_absolute(string) == 1)
		{
			exec_absolute(string, environ);
			continue;
		}
		if (string[numc_har - 1] == '\n')
			string[numc_har - 1] = '\0';
		if (string == NULL)
			continue;
		if (string[0] != '\0')
		{
			if (custom_strcmp(string, "exit") == 0)
			{
				free(string);
				break;
			}
			execute_command(string, environ);
		}
		free(string);
	}
}
