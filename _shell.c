#include "main.h"

/**
 * hsh - main shell loop
 * @infos: the parameter & return info struct
 * @_av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *infos, char **_av)
{
	ssize_t s = 0;
	int _builtin_ret = 0;

	while (s != -1 && _builtin_ret != -2)
	{
		remove_info(infos);
		if (active(infos))
			_puts("George-Peda=>$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(infos);
		if (s != -1)
		{
			s_info(infos, _av);
			_builtin_ret = find_builtin(infos);
			if (_builtin_ret == -1)
				find_cmd(infos);
		}
		else if (active(infos))
			_putchar('\n');
		let_info(infos, 0);
	}
	write_history(infos);
	let_info(infos, 1);
	if (!active(infos) && infos->status)
		exit(infos->status);
	if (_builtin_ret == -2)
	{
		if (infos->err_num == -1)
			exit(infos->status);
		exit(infos->err_num);
	}
	return (_builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @infos: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *infos)
{
	int a, _built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _env},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _set_env},
		{"unsetenv", _unset_env},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(infos->argv[0], builtintbl[a].type) == 0)
		{
			infos->line_count++;
			_built_in_ret = builtintbl[a].func(infos);
			break;
		}
	return (_built_in_ret);
}

/**
 * _cmd - finds a command in PATH
 * @infos: the parameter & return info struct
 *
 * Return: void
 */
void _cmd(info_t *infos)
{
	char *path = NULL;
	int a, c;

	infos->path = infos->argv[0];
	if (infos->linecount_flag == 1)
	{
		infos->line_count++;
		infos->linecount_flag = 0;
	}
	for (a = 0, c = 0; infos->arg[a]; a++)
		if (!_delimeter(infos->arg[a], " \t\n"))
			c++;
	if (!c)
		return;

	path = find_path(infos, get_env(infos, "PATH="), infos->argv[0]);
	if (path)
	{
		infos->path = path;
		fork_cmd(infos);
	}
	else
	{
		if ((active(infos) || get_env(infos, "PATH=")
			|| infos->argv[0][0] == '/') && is_cmd(infos, infos->argv[0]))
			fork_cmd(infos);
		else if (*(infos->arg) != '\n')
		{
			infos->status = 127;
			print_error(infos, "not found\n");
		}
	}
}

/**
 * _fork_cmd - forks a an exec thread to run cmd
 * @infos: the parameter & return info struct
 *
 * Return: void
 */
void _fork_cmd(info_t *infos)
{
	pid_t _child_pid;

	_child_pid = fork();
	if (_child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (_child_pid == 0)
	{
		if (execve(infos->path, infos->argv, get_environ(infos)) == -1)
		{
			let_info(infos, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infos->status));
		if (WIFEXITED(infos->status))
		{
			infos->status = WEXITSTATUS(infos->status);
			if (infos->status == 126)
				print_error(infos, "Permission denied\n");
		}
	}
}
