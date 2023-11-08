#include "main.h"

/**
 * add_node - adds a node to the start of the list
 * @_head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **_head, const char *str, int num)
{
	list_t *my_new_head;

	if (!_head)
		return (NULL);
	my_new_head = malloc(sizeof(list_t));
	if (!my_new_head)
		return (NULL);
	memset((void *)my_new_head, 0, sizeof(list_t));
	my_new_head->num = num;
	if (str)
	{
		my_new_head->str = _strdup(str);
		if (!my_new_head->str)
		{
			free(my_new_head);
			return (NULL);
		}
	}
	my_new_head->next = *_head;
	*_head = my_new_head;
	return (my_new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @_head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **_head, const char *str, int num)
{
	list_t *my_new_node, *node;

	if (!_head)
		return (NULL);

	node = *_head;
	my_new_node = malloc(sizeof(list_t));
	if (!my_new_node)
		return (NULL);
	memset((void *)my_new_node, 0, sizeof(list_t));
	my_new_node->num = num;
	if (str)
	{
		my_new_node->str = _strdup(str);
		if (!my_new_node->str)
		{
			free(my_new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = my_new_node;
	}
	else
		*_head = my_new_node;
	return (my_new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @_h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *_h)
{
	size_t a = 0;

	while (_h)
	{
		_puts(_h->str ? _h->str : "(nil)");
		_puts("\n");
		_h = _h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node at given index
 * @_head: address of pointer to first node
 * @_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **_head, unsigned int _index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!_head || !*_head)
		return (0);

	if (!_index)
	{
		node = *_head;
		*_head = (*_head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *_head;
	while (node)
	{
		if (a == _index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @_head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **_head_ptr)
{
	list_t *node, *next_node, *_head;

	if (!_head_ptr || !*_head_ptr)
		return;
	_head = *_head_ptr;
	node = _head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*_head_ptr = NULL;
}
