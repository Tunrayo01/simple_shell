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

/* Command type constants */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Buffer parameters */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Conversion flags */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Feature configuration */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* History-related constants */
#define HISTORY_FILE "my_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * struct StringList - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct StringList
{
		int num;
		char *str;
		struct StringList *next;
} StringList_t;

/**
 * struct shellInfo - pointer struct parameter
 * @arg: command line arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @fname: the program filename
 * @env_list: linked list local copy of environ
 * @custom_env: custom modified copy of environ from env_list
 * @history_list: the history node
 * @alias_list: the alias node
 * @env_changed: on if environ was changed
 * @execution_status: the return status of the last exec'd command
 * @command_buffer: address of pointer to command_buffer, on if chaining
 * @command_buffer_type: COMMAND_type ||, &&, ;
 * @read_file_descriptor: the file descriptor from which to read line input
 * @history_count: the history line number count
 * @argument_count: the argument count
 * @line_count: the error count
 * @error_number: the error code for exit()s
 * @line_count_flag: if on count this line of input
 */
typedef struct shellInfo
{
		char *arg;
		char **argv;
		char *path;
		int argument_count;
		unsigned int line_count;
		int error_number;
		int line_count_flag;
		char *fname;
		StringList_t *env_list;
		StringList_t *history_list;
		StringList_t *alias_list;
		char **custom_env;
		int env_changed;
		int execution_status;

		char **command_buffer;
		int command_buffer_type;
		int read_file_descriptor;
		int history_count;
}
shellInfo_t;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct BuiltinCommand - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct BuiltinCommand
{
		char *type;
		int (*func)(shellInfo_t *);
} BuiltinCommand_t;

/* Function prototypes */

/* Path command */
int is_shell_command(shellInfo_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(shellInfo_t *, char *, char *);
int loop_shell(char **);
int shell(shellInfo_t *, char **);
void find_builtin_command(shellInfo_t *);
void find_shell_command(shellInfo_t *);
void fork_shell_command(shellInfo_t *);

/* String error printer */
void print_error_message(char *);
int put_char_fd(char, int);
int put_string_fd(char *, int);

/* Built string functions */
int string_length(char *);
int string_compare(char *, char *);
char *starts_with(const char *, const char *);
char *string_concat(char *, char *);
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int put_char(char);
char *string_copy_n(char *, char *, int);
char *string_concat_n(char *, char *, int);
char *string_character(char *, char);
char **parse_string(char *, char *);
char **split_string(char *, char);

/* Memory functions */
char *memory_set(char *, char, unsigned int);
void free_memory(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);
int free_block(void **);

/* More string and number functions */
int is_shell_active(shellInfo_t *);
int is_delimiter(char, char *);
int is_alpha_character(int);
int string_to_integer(char *);
int error_string_to_integer(char *);
void print_error_message(shellInfo_t *, char *);
int print_integer(int, int);
char *convert_integer(long int, int, int);
void remove_comments(char *);

/* Advance commands */
int my_exit(shellInfo_t *);
int my_cd(shellInfo_t *);
int my_help(shellInfo_t *);
int my_history(shellInfo_t *);
int my_alias(shellInfo_t *);

/* Getline function */
ssize_t get_user_input(shellInfo_t *);
int shell_getline(shellInfo_t *, char **, size_t *);
void handle_sigint(int);

/* Add-on functions for info struct */
void clear_info(shellInfo_t *);
void set_info(shellInfo_t *, char **);
void finalize_info(shellInfo_t *, int);

/* Dealing with environmental variable */
char *get_environment_variable(shellInfo_t *, const char *);
int my_env(shellInfo_t *);
int set_environment_variable(shellInfo_t *);
int unset_environment_variable(shellInfo_t *);
int put_env_list(shellInfo_t *);
char **get_custom_environment(shellInfo_t *);
int my_unsetenv(shellInfo_t *, char *);
int my_setenv(shellInfo_t *, char *, char *);

/* History functions */
char *get_history_file(shellInfo_t *);
int write_history(shellInfo_t *);
int read_history(shellInfo_t *);
int build_history_list(shellInfo_t *, char *, int);
int renumber_history(shellInfo_t *);

/* List functionalities */
StringList_t *add_node(StringList_t **, const char *, int);
StringList_t *add_node_end(StringList_t **, const char *, int);
size_t print_list_string(const StringList_t *);
int delete_node_at_index(StringList_t **, unsigned int);
void free_string_list(StringList_t **);
size_t list_length(const StringList_t *);
char **list_to_strings(StringList_t *);
size_t print_list(const StringList_t *);
StringList_t *node_starts_with(StringList_t *, char *, char);
ssize_t get_node_index(StringList_t *, StringList_t *);

/* Chain commands */
int is_command_chain(shellInfo_t *, char *, size_t *);
void check_command_chain(shellInfo_t *, char *, size_t *, size_t, size_t);
int replace_alias(shellInfo_t *);
int replace_variables(shellInfo_t *);
int replace_substring(char **, char *);

#endif
