#include "main.h"
/**
 * free_args - Free the allocated memory for the arguments array
 * @args: The array of arguments to free
 * Return: void
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}
/**
 * tokenize_input - Tokenize the input command with arguments
 * @command: The command to tokenize
 * Return: Array of arguments
 */
char **tokenize_input(char *command)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token = NULL;

	if (!tokens)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(command, " \t\n\r\a");
	while (token != NULL)
	{
		tokens[position] = custom_strdup(token);
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				return (NULL);
			}
		}

		token = strtok(NULL, " \t\n\r\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
/**
 * handle_builtin - Handle the execution of a built-in command
 * @command: The built-in command to handle
 * Return: void
 */
void handle_builtin(char *command)
{
	if (custom_strcmp(command, "exit") == 0)
	{
	exit(EXIT_SUCCESS);
	}
}
/**
 * is_builtin - Check if the command is a built-in command
 * @command: The command to check
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char *command)
{
	return (custom_strcmp(command, "exit") == 0);
}
/**
 * find_full_path - Find the full path in the PATH environment variable.
 * @command: The command to find.
 *
 * Return: A pointer to a string containing the full path of the command,
 *         or NULL if the command is not found or encounters an error.
 */
char *find_full_path(char *command)
{
	char *dir = NULL, *path_env = custom_getenv_or_error("PATH");
	char *full_path = NULL;
	int flag = 0;
	char *path_env_copy = custom_strdup(path_env);

	dir = strtok(path_env_copy, ":");

	while (dir != NULL)
	{
		size_t dir_len = custom_strlen(dir);
		size_t command_len = custom_strlen(command);

		full_path = (char *)malloc(dir_len + command_len + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			break;
		}

		custom_strcpy(full_path, dir, dir_len + 1);
		if (full_path[dir_len - 1] != '/')
		{
			custom_strcat(full_path, "/");
		}
		custom_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			flag = 1;
			break;
		}
		free(full_path);
		full_path[dir_len] = '0';
		dir = strtok(NULL, ":");
	}
	free(path_env_copy);
	if (flag)
		return (full_path);
	return (NULL);
}
