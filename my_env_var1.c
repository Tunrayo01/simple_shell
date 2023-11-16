#include "my_shell.h"

/**
 * get_shell_environment - Returns the string array copy of our
 * shell environment.
 * @info: Pointer to the parameter struct.
 *
 * Return: Always 0.
 */
char **get_shell_environment(info_t *info)
{
	if (!info->shell_environment || info->environment_changed)
	{
		info->shell_environment = list_to_strings(info->env);
		 info->environment_changed = 0;
	}

	return (info->shell_environment);
}

/**
 * _unset_shell_env - Removes an environment
 * variable from the shell environment.
 * @info: Pointer to the parameter struct.
 * @var: The string representation of the environment variable.
 *
 * Return: 1 on successful delete, 0 otherwise.
 */
int _unset_shell_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->env),
					index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->environment_changed);
}

/**
 * _set_shell_env - Initializes a new environment variable or
 * modifies an existing one
 *                  in the shell environment.
 * @info: Pointer to the parameter struct.
 * @var: The string representation of the environment variable.
 * @value: The string value of the environment variable.
 *
 * Return: Always 0.
 */
int _set_shell_env(info_t *info, char *var, char *value)
{
	char *env_variable = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	env_variable = malloc(_strlen(var) + _strlen(value) + 2);
	if (!env_variable)
		return (1);

	_strcpy(env_variable, var);
	_strcat(env_variable, "=");
	_strcat(env_variable, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = env_variable;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), env_variable, 0);
	free(env_variable);
	info->environment_changed = 1;
	return (0);
}

