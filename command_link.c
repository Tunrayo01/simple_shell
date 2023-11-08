#include  "main.h"

/**
 * _is_chain - test if current char in buffer is a chain delimeter
 * @infos: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _is_chain(info_t *infos, char *buf, size_t *q)
{
	size_t b = *q;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		infos->cmd_buf_type = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		infos->cmd_buf_type = CMD_AND;
	}
	/* finding  end of this command */
	else if (buf[b] == ';')
	{
		/* replacin the  semicolon with null */
		buf[b] = 0;
		infos->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = b;
	return (1);
}

/**
 * _check_chain - checks we should continue chaining based on last status
 *@infos: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 * @a: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void _check_chain(info_t *infos, char *buf, size_t *q, size_t a, size_t len)
{
	size_t b = *q;

	if (infos->cmd_buf_type == CMD_AND)
	{
		if (infos->status)
		{
			buf[a] = 0;
			b = len;
		}
	}
	if (infos->cmd_buf_type == CMD_OR)
	{
		if (!infos->status)
		{
			buf[a] = 0;
			b = len;
		}
	}

	*q = b;
}

/**
 * _replace_alias - replaces an aliases in the tokenized string
 * @infos: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_alias(info_t *infos)
{
	int a;
	list_t *node;
	char *q;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(infos->alias, infos->argv[0], '=');
		if (!node)
			return (0);
		free(infos->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		infos->argv[0] = q;
	}
	return (1);
}

/**
 * _replace_vars - replaces vars in the tokenized string
 * @infos: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_vars(info_t *infos)
{
	int a = 0;
	list_t *node;

	for (a = 0; infos->argv[a]; a++)
	{
		if (infos->argv[a][0] != '$' || !infos->argv[a][1])
			continue;

		if (!_strcmp(infos->argv[a], "$?"))
		{
			replace_string(&(infos->argv[a]),
					_strdup(convert_number(infos->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infos->argv[a], "$$"))
		{
			replace_string(&(infos->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infos->env, &infos->argv[a][1], '=');
		if (node)
		{
			replace_string(&(infos->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infos->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * _replace_string - replaces string
 * @my_old: address of old string
 * @my_new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_string(char **my_old, char *my_new)
{
	free(*my_old);
	*my_old = my_new;
	return (1);
}
