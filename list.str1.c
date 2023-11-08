#include "main.h"

/**
 * list_len - determines length of linked list
 * @_h: pointer to first node
 *
 * Return: size of list
 */

size_t list_len(const list_t *_h)

{

	size_t a = 0;



	while (_h)

	{

		_h = _h->next;

		a++;

	}

	return (a);

}



/**
 * list_to_strings - returns an array of strings of the list->str
 * @_head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *_head)

{

	list_t *node = _head;

	size_t a = list_len(_head), b;

	char **strs;

	char *str;

	if (!_head || !a)

		return (NULL);

	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)

		return (NULL);
	for (a = 0; node; node = node->next, a++)

	{

		str = malloc(_strlen(node->str) + 1);

		if (!str)
		{

			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;

	}
	strs[a] = NULL;
	return (strs);

}


/**
 * print_list - prints all elements of a list_t linked list
 * @_h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list(const list_t *_h)

{

	size_t a = 0;

	while (_h)

	{
		_puts(convert_number(_h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(_h->str ? _h->str : "(nil)");
		_puts("\n");
		_h = _h->next;

		a++;
	}
	return (a);

}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @_prefix: string to match
 * @_c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *_prefix, char _c)
{

	char *q = NULL;

	while (node)

	{
		q = starts_with(node->str, _prefix);

		if (q && ((_c == -1) || (*q == _c)))

			return (node);

		node = node->next;

	}
	return (NULL);

}


/**
 * get_node_index - gets the index of a node
 * @_head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *_head, list_t *node)

{

	size_t a = 0;

	while (_head)

	{

		if (_head == node)

			return (a);

		_head = _head->next;

		a++;

	}

	return (-1);
}
