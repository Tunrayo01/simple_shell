#include "my_shell.h"

/**
 * is_command_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_command_chain(shellInfo_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->command_buffer_type = COMMAND_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->command_buffer_type = COMMAND_AND;
	}
	/* found end of this command */
	else if (buf[j] == ';')
	{
		/* replace semicolon with null */
		buf[j] = 0;
		info->command_buffer_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_command_chain - checks if we should continue chaining based on
 * the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_command_chain(shellInfo_t *info, char *buf, size_t *p,
		size_t i, size_t len)
{
	size_t j = *p;

	if (info->command_buffer_type == COMMAND_AND)
	{
		if (info->execution_status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->command_buffer_type == COMMAND_OR)
	{
		if (!info->execution_status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_command_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_alias(shellInfo_t *info)
{
	int i;
	StringList_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias_list, info->argv[0], '=');
		if (!node)
			return (0);
		free_memory((void **)&(info->argv[0]));
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = string_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_command_variables - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_variables(shellInfo_t *info)
{
	int i = 0;
	StringList_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					string_duplicate(convert_integer(info->execution_status,
							10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						string_duplicate(convert_integer(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env_list, &(info->argv[i][1]), '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
								string_duplicate(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&(info->argv[i]), string_duplicate(""));
	}
	return (0);
}

/**
 * replace_string_value - replaces string value
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string_value(char **old, char *new)
{
	free_memory((void **)old);
	*old = new;
	return (1);
}

