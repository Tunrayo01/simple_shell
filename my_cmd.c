#include "my_shell.h"
/**
 * bele_cmd - main command entry
 * @my_cmds: cmd parsed into the functions
 * @bel_size: size of command parsed into the function
 */
void my_cmds(char **my_cmds, size_t *bel_size)
{
	ssize_t special_read;

	special_read = my_getline(my_cmds, bel_size);

	if (special_read == -1)
	{
		if (*my_cmds == NULL)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}

		if (feof(stdin))
		{
			_shell("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	if ((*my_cmds)[special_read - 1] == '\n')
	{
		(*my_cmds)[special_read - 1] = '\0';
		*bel_size = strlen(*my_cmds);
	}
}
