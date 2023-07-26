#include "main.h"
/**
 * error - Entry point
 * Description: 'do the error part and free any memory'
 * @cmdinput: 'the memory to free when error occur'
 * @argv: 'arguement vector'
 * Return: void
 */
void error(char *cmdinput, char argv[])
{
	perror(argv);
	free(cmdinput);
	exit(1);
}
