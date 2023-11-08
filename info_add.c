#include "main.h"

/**
 * _remove_info - initializes info_t struct in the program
 * @infos: struct address
 */
void _remove_info(info_t *infos)
{
	infos->arg = NULL;
	infos->argv = NULL;
	infos->path = NULL;
	infos->argc = 0;
}

/**
 * s_info - initializes info_t struct
 * @infos: struct address
 * @_av: argument vector
 */
void s_info(info_t *infos, char **_av)
{
	int a = 0;

	infos->fname = _av[0];
	if (infos->arg)
	{
		infos->argv = parse(infos->arg, " \t");
		if (!infos->argv)
		{

			infos->argv = malloc(sizeof(char *) * 2);
			if (infos->argv)
			{
				infos->argv[0] = _strdup(infos->arg);
				infos->argv[1] = NULL;
			}
		}
		for (a = 0; infos->argv && infos->argv[a]; a++)
			;
		infos->argc = a;

		replace_alias(infos);
		replace_vars(infos);
	}
}

/**
 * let_info - frees info_t struct fields
 * @infos: struct address
 * @_all: true if freeing all fields
 */
void let_info(info_t *infos, int _all)
{
	ffree(infos->argv);
	infos->argv = NULL;
	infos->path = NULL;
	if (_all)
	{
		if (!infos->cmd_buf)
			free(infos->arg);
		if (infos->env)
			free_list(&(infos->env));
		if (infos->history)
			free_list(&(infos->history));
		if (infos->alias)
			free_list(&(infos->alias));
		ffree(infos->environ);
			infos->environ = NULL;
		bfree((void **)infos->cmd_buf);
		if (infos->readfd > 2)
			close(infos->readfd);
		_putchar(BUF_FLUSH);
	}
}
