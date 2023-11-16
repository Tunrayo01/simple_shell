#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* for command parameter */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* buffer parameters */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".mysimple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo -  pointer struct parameter
 *@arg: command line arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} shellinfo_t;

#define	SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(shellinfo_t *);
} builtin_table;

/* path command  */
int _is_cmd(shellinfo_t *, char *);
char *dupl_char(char *, int, int);
char *find_path(shellinfo_t *, char *, char *);
int loophsh(char **);
int hsh(shellinfo_t *, char **);
int find_builtin(shellinfo_t *);
void find_cmd(shellinfo_t *);
void fork_cmd(shellinfo_t *);

/* string error printer */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* built string function*/
int _strlent(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcatn(char *, char *);
char *_strcopy(char *, char *);
char *_strdupl(const char *);
void _puts(char *);
int _putchar(char);
char *_strncopy(char *, char *, int);
char *_strncatn(char *, char *, int);
char *_strchr(char *, char);
char **parse(char *, char *);
char **strtow2(char *, char);

/* memory_functions */
char *my_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* more string and number func */
int active(shellinfo_t *);
int _delimete(char, char *);
int _alpha_char(int);
int _atoic(char *);
int _erratoic(char *);
void prints_error(shellinfo_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comment(char *);

/* advance commands */
int _my_exit(shellinfo_t *);
int _my_cd(shellinfo_t *);
int _my_help(shellinfo_t *);
int _my_history(shellinfo_t *);
int _my_alias(shellinfo_t *);

/* getline function */
ssize_t my_get_input(shellinfo_t *);
int my_getline(shellinfo_t *, char **, size_t *);
void my_sigintHandler(int);

/* add on functions for infor struct */
void remove_info(shellinfo_t *);
void s_info(shellinfo_t *, char **);
void let_info(shellinfo_t *, int);

/* dealing with enviromental varaible */
char *my_get_env(shellinfo_t *, const char *);
int my_env(shellinfo_t *);
int set_env(shellinfo_t *);
int _unset_env(shellinfo_t *);
int put_env_list(shellinfo_t *);
char **my_get_environ(shellinfo_t *);
int _unsetenv(shellinfo_t *, char *);
int _setenv(shellinfo_t *, char *, char *);

/* history functions */
char *get_history_file(shellinfo_t *info);
int mywrite_history(shellinfo_t *info);
int myread_history(shellinfo_t *info);
int build_history_list(shellinfo_t *info, char *buf, int linecount);
int renumber_myhistory(shellinfo_t *info);

/* list functionalities */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain commands  */
int ismy_chain(shellinfo_t *, char *, size_t *);
void check_chain(shellinfo_t *, char *, size_t *, size_t, size_t);
int myreplace_alias(shellinfo_t *);
int myreplace_vars(shellinfo_t *);
int replace_string(char **, char *);

#endif
