/* the concluding part of command line in shell program*/
#include "main.h"

/**
 * _my_history - displays the history list
 *              with line numbers, starting at 0.
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_history(info_t *infos)
{
	print_list(infos->history);
	return (0);
}

/**
 * unsetalias - sets alias to string
 * @infos: parameter struct
 * @estr: the string alias to unset
 *
 * unset alias by removing it from alias list
 * Return: Always 0 on success, 1 on error
 */
int unsetalias(info_t *infos, char *estr)
{
	char *q, e;
	int rete;

	q = _strchr(estr, '=');
	if (!q)
		return (1);
	e = *q;
	*q = 0;
	rete = delete_node_at_index(&(infos->alias),
		get_node_index(infos->alias, node_starts_with(infos->alias, estr, -1)));
	*q = e;
	return (rete);
}

/**
 * setalias - sets alias to string
 * @infos: parameter struct
 * @estr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setalias(info_t *infos, char *estr)
{
	char *q;

	q = _strchr(estr, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unsetalias(infos, estr));

	unsetalias(infos, estr);
	return (add_node_end(&(infos->alias), estr, 0) == NULL);
}

/**
 * printalias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printalias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics the alias builtin (man alias)
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_alias(info_t *infos)
{
	int a = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (infos->argc == 1)
	{
		node = infos->alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; infos->argv[a]; a++)
	{
		q = _strchr(infos->argv[a], '=');
		if (q)
			setalias(infos, infos->argv[a]);
		else
			printalias(node_starts_with(infos->alias, infos->argv[a], '='));
	}

	return (0);
}
