#include "my_shell.h"
/**
 * my_env - prints environment variable to stdout
 * @spec_env: envs
 */
void my_env(char **spec_env)
{
	int clay;

	for (clay = 0; spec_env[clay] != NULL; clay++)
	{
		_shell(spec_env[clay]);
		my_putchar('\n');
	}
}
