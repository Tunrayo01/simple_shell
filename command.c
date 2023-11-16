#include "my_shell.h"

/**
 * _exit_shell - Exits the shell with a given exit status.
 * @info: Pointer to the parameter struct.
 *
 * Return: Exits the shell with the specified exit status.
 *         (0) if info->argv[0] != "exit"
 */
int _exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _change_directory - Changes the current directory of the process.
 * @info: Pointer to the parameter struct.
 *
 * Return: Always 0.
 */
int _change_directory(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		new_dir = get_env(info, "HOME=");
		if (!new_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((new_dir = get_env(info, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
	{
			_puts(current_dir);
			_putchar('\n');
				return (1);
		}
			_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((new_dir = get_env(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		 _setenv(info, "OLDPWD", get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _show_help - Displays help information.
 * @info: Pointer to the parameter struct.
 *
 * Return: Always 0.
 */
int _show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help: Function not yet implemented.\n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
		return (0);
}
