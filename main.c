#include "main.h"
/**
 * main - Entry point
 * Description: 'the shell programme'
 * @argc: arguemnt count
 * @argv: arguement vector
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	if (argc >= 1)
		prompt(environ, argv[0]);
	return (0);
}
