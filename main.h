#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

extern char **environ;
void prompt(char **environ, char argv[]);
void error(char *cmdinput, char argv[]);

#endif
