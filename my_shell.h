#ifndef MY_SHELL_H
#define MY_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
void my_cmds(char **bel_cmd, size_t *bel_sizes);
void my_env(char **spec_envs);
ssize_t my_getline(char **my_buff, size_t *my_size);
void my_prompt(void);
int my_putchar(char my_char);
int my_putchar(char my_char);
void _execute(const char *my_cmd_line);
int _shell(const char *string);
#endif
