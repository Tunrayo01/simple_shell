#include "my_shell.h"

/**
 * shell_loop - Main shell loop
 * @info_struct: Pointer to the parameter and return info struct
 * @args: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info_struct, char **args)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_info(info_struct);
		if (is_shell_active(info_struct))
			_puts("MyShell=>$ ");
		_eputchar(BUF_FLUSH);
		input_result = get_user_input(info_struct);
		if (input_result != -1)
		{
			set_info(info_struct, args);
			builtin_result = find_builtin_command(info_struct);
			if (builtin_result == -1)
				find_shell_command(info_struct);
		}
		else if (is_shell_active(info_struct))
			_putchar('\n');
		finalize_info(info_struct, 0);
	}
	write_history(info_struct);
	finalize_info(info_struct, 1);
	if (!is_shell_active(info_struct) && info_struct->status)
		exit(info_struct->status);
	if (builtin_result == -2)
	{
		if (info_struct->err_num == -1)
			exit(info_struct->status);
		exit(info_struct->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - Finds a builtin command
 * @info_struct: Pointer to the parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(info_t *info_struct)
{
	int i, builtin_result = -1;
	builtin_table builtin_table[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtin_table[i].type; i++)
		if (_strcmp(info_struct->argv[0], builtin_table[i].type) == 0)
		{
			info_struct->line_count++;
			builtin_result = builtin_table[i].func(info_struct);
			break;
		}
	return (builtin_result);
}

/**
 * find_shell_command - Finds a command in PATH
 * @info_struct: Pointer to the parameter and return info struct
 *
 * Return: void
 */
void find_shell_command(info_t *info_struct)
{
	char *path = NULL;
	int i, arg_count;

	info_struct->path = info_struct->argv[0];
	if (info_struct->linecount_flag == 1)
	{
		info_struct->line_count++;
		info_struct->linecount_flag = 0;
	}
	for (i = 0, arg_count = 0; info_struct->arg[i]; i++)
		if (!_is_delimeter(info_struct->arg[i], " \t\n"))
			arg_count++;
	if (!arg_count)
		return;

	path = find_command_path(info_struct, get_env(info_struct, "PATH="),
			info_struct->argv[0]);
	if (path)
	{
		info_struct->path = path;
		execute_command(info_struct);
	}
	else
	{
		if ((is_shell_active(info_struct) || get_env(info_struct, "PATH=")
				|| info_struct->argv[0][0] == '/') && is_shell_command
				(info_struct, info_struct->argv[0]))
			execute_command(info_struct);
		else if (*(info_struct->arg) != '\n')
		{
			info_struct->status = 127;
			print_error_message(info_struct, "not found\n");
		}
	}
}

/**
 * execute_command - Forks an exec thread to run a command
 * @info_struct: Pointer to the parameter and return info struct
 *
 * Return: void
 */
void execute_command(info_t *info_struct)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info_struct->path, info_struct->argv,
					get_environ(info_struct)) == -1)
		{
			finalize_info(info_struct, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info_struct->status));
		if (WIFEXITED(info_struct->status))
		{
			info_struct->status = WEXITSTATUS(info_struct->status);
			if (info_struct->status == 126)
				print_error_message(info_struct, "Permission denied\n");
		}
	}
}
