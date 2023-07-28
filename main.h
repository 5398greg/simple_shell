#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

extern char **environ;
void prompt(char **environ);
void execute_command(char *command, char **environ);
int custom_strcmp(const char *str1, const char *str2);
char **tokenize_input(char *command);
void free_args(char **args);
char *find_full_path(char *command);
void handle_builtin(char *command);
int is_builtin(char *command);
char *custom_getenv(const char *name, char **environ);
int custom_strncmp(const char *str1, const char *str2, size_t n);
unsigned int custom_strlen(const char *str);
char *custom_strcat(char *dest, const char *src);
char *custom_strcpy(char *dest, const char *src, size_t des_size);
char *custom_strdup(const char *str);
char *custom_getenv_or_error(const char *name);

#endif
