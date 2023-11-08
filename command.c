/* The program below is a command program of a simple shell*/
#include "main.h"

/**
 * _my_exit - basically exits the shell but can take arguments
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype in the program
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _my_exit(info_t *infos)
{
	int exit_check;

	if (infos->argv[1])  /* If there is an exit arguement */
	{
		exit_check = _atoi(infos->argv[1]);
		if (exit_check == -1)
		{
			infos->status = 2;
			print_error(infos, "Illegal number: ");
			_eputs(infos->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infos->err_num = _atoi(infos->argv[1]);
		return (-2);
	}
	infos->err_num = -1;
	return (-2);
}

/**
 * _my_cd - changes the current directory of the process
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_cd(info_t *infos)
{
	char *r, *dir, buffer[1024];
	int chdiret;

	r = getcwd(buffer, 1024);
	if (!r)
		_puts("TODO: >>get_cwd failure e_msg here<<\n");
	if (!infos->argv[1])
	{
		dir = get_env(infos, "HOME=");
		if (!dir)
			chdiret = /* TODO: what should this be? */
				chdir((dir = get_env(infos, "PWD=")) ? dir : "/");
		else
			chdiret = chdir(dir);
	}
	else if (_strcmp(infos->argv[1], "-") == 0)
	{
		if (!get_env(infos, "OLDPWD="))
		{
			_puts(r);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(infos, "OLDPWD=")), _putchar('\n');
		chdiret = /* TODO: what should this be? */
			chdir((dir = get_env(infos, "OLDPWD=")) ? dir : "/");
	}
	else
		chdiret = chdir(infos->argv[1]);
	if (chdiret == -1)
	{
		print_error(infos, "cannot cd to ");
		_eputs(infos->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infos, "OLDPWD", get_env(infos, "PWD="));
		_setenv(infos, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _my_help - changes the current directory of the process
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_help(info_t *infos)
{
	char **argarray;

	argarray = infos->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argarray); /* temp att_unused workaround */
	return (0);
}
