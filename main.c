#include "main.h"
/**
 * main - Entry point
 * Description: 'the shell programme'
 * Return: Always 0 (Success)
 */
int main(void)
{
	bool frompipe = false;

	prompt(environ, frompipe);
	return (0);
}
