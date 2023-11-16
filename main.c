#include "my_shell.h"

/**
 * main - main__programs to be executed
 * @argc: counting of argumen to be executed
 * @argv: argum_var in the main function
 * @_env: env_enviroment in the kernel
 * Return: 0 or 1
 */
int main(int argc, char *argv[], char **_env)
{

	char *bel_cmd;
	size_t bel_size;
	int my_exitstatus;
	size_t my_newlinepos;
	(void)argv;
	(void)argc;

	bel_cmd = NULL;
	my_exitstatus = 0;

	while (1)
	{
		if (isatty(0) == 1)
			my_prompt();
		my_cmds(&bel_cmd, &bel_size);

		if (strcmp(bel_cmd, "exit") == 0)
		{
			break;
		}
		else if (strncmp(bel_cmd, "exit ", 5) == 0)
		{
			my_exitstatus = atoi(bel_cmd + 5);
			break;
		}
		else if (strcmp(bel_cmd, "_env") == 0 || strcmp(bel_cmd, "printenv") == 0)
			my_env(_env);
		_execute(bel_cmd);

		my_newlinepos = strcspn(bel_cmd, "\n");
		if (my_newlinepos < bel_size)
			bel_cmd[my_newlinepos] = '\0';

		if (bel_cmd != NULL)
			bel_cmd = NULL;
	}

	return (my_exitstatus);
}
