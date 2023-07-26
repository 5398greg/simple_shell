#include "main.h"
/**
 * error - Entry point
 * Description: 'do the error part and free any memory'
 * @cmdinput: 'the memory to free when error occur'
 * Return: void
 */
void error(char *cmdinput)
{
	perror("Error ");
	free(cmdinput);
	exit(EXIT_FAILURE);
}
