#include "main.h"
/**
 * main - Entry point
 * Description: 'the shell programme'
 * @argc: argument count
 * @argv: argurment vector
 * @env: environment variable
 * Return: Always 0 (Success)
 */
int main(void)
{
	int argc = 1;
	if(argc == 1)
		prompt(environ);
	return (0);
}
