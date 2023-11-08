#include "main.h"

/**
 * my_env - prints the current environment variables
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(info_t *infos)
{
	print_list_str(infos->env);
	return (0);
}

/**
 * myget_env - gets the value of an environ variable
 * @infos: Structure containing potential arguments. Used to maintain
 * @_name: env var name
 *
 * Return: the value
 */
char *myget_env(info_t *infos, const char *_name)
{
	list_t *node = infos->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, _name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _set_env(info_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);
	return (1);
}

/**
 * _unset_env - Remove an environment variable
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _unset_env(info_t *infos)
{
	int a;

	if (infos->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= infos->argc; a++)
		_unsetenv(infos, infos->argv[a]);

	return (0);
}

/**
 * put_env_list - populates env linked list
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int put_env_list(info_t *infos)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	infos->env = node;
	return (0);
}
