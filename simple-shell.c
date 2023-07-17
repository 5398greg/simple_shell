#include "main.h"
/**
 * main - Entry point
 * Description:'its for displaying prompt for shell'
 * Return: Always 0 (Success)
 */

int main(void)
{
char *prompt = "$ ", *buff = NULL;
size_t n;
int getlno, bytes, wpid;
bool frompipe = false;

while (1)
{
	if (isatty(STDIN_FILENO) == 0)
		frompipe = true;

write(STDOUT_FILENO, prompt, 2);
buff = malloc(sizeof(char) * n);
bytes = getline(&buff, &n, stdin);
if (bytes == -1)
{
	perror("Getline error/n");
	free(buff);
	exit(EXIT_FAILURE);
}
if (buff[bytes - 1] == '\n')
buff[bytes - 1] = '\0';
}
free(buff);
return (0);
}
