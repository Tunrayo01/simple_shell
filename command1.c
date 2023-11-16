#include "my_shell.h"

/**
 * display_history - Displays the history list with line numbers.
 * @info: Shell information structure.
 * Return: Always 0.
 */
int display_history(shellInfo_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias from the alias list.
 * @info: Shell information structure.
 * @alias_str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error.
 */
int remove_alias(shellInfo_t *info, char *alias_str)
{
	char *equal_sign, temp;
	int ret;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

		temp = *equal_sign;
		*equal_sign = 0;

	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with
			(info->alias, alias_str, -1)));

	*equal_sign = temp;
	return (ret);
}

/**
 * set_alias - Sets an alias in the alias list.
 * @info: Shell information structure.
 * @alias_str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(shellInfo_t *info, char *alias_str)
{
	char *equal_sign;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return remove_alias(info, alias_str);

	remove_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: Alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(StringList_t *node)
{
	char *equal_sign = NULL, *alias = NULL;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias = node->str; alias <= equal_sign; alias++)
			put_char(*alias);
		put_char('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Manages aliases, either displaying existing aliases
 *                or setting new ones based on command arguments.
 * @info: Shell information structure.
 *
 * Return: Always 0.
 */
int manage_alias(shellInfo_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	StringList_t *node = NULL;

	if (info->argument_count == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

