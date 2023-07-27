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
void prompt(char **environ);
void error(char *cmdinput, char argv[]);
void execute_command(char *command, char **environ);
int custom_strcmp(const char* str1, const char* str2);
char *read_input(int *is_interactive);

#endif
