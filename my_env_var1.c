#include "main.h"

/**
 * _get_environ - returns the string array copy of our environ
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_get_environ(info_t *infos)
{
	if (!infos->environ || infos->env_changed)
	{
		infos->environ = list_to_strings(infos->env);
		infos->env_changed = 0;
	}

	return (infos->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @_var: the string env var property
 */
int _unsetenv(info_t *infos, char *_var)
{
	list_t *node = infos->env;
	size_t a = 0;
	char *q;

	if (!node || !_var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, _var);
		if (q && *q == '=')
		{
			infos->env_changed = delete_node_at_index(&(infos->env), a);
			a = 0;
			node = infos->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (infos->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @_var: the string env var property
 * @_value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *infos, char *_var, char *_value)
{
	char *buf = NULL;
	list_t *node;
	char *q;

	if (!_var || !_value)
		return (0);

	buf = malloc(_strlen(_var) + _strlen(_value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, _var);
	_strcat(buf, "=");
	_strcat(buf, _value);
	node = infos->env;
	while (node)
	{
		q = starts_with(node->str, _var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			infos->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infos->env), buf, 0);
	free(buf);
	infos->env_changed = 1;
	return (0);
}
