#include "my_shell.h"
/**
 * _getline - main program to read on the shell program
 * @my_buf: buffer storage on the program
 * @shoc_size: size read buffer
 * Return: a signed int anytime being called
 */
ssize_t _getline(char **my_buf, size_t *shoc_size)
{
	static char shoc_staticbuff[1024];

	ssize_t shoc_numread;

	*my_buf = NULL;

	if (*my_buf == NULL)
	{
		*my_buf = shoc_staticbuff;
	}
	*shoc_size = sizeof(shoc_staticbuff);

	shoc_numread = read(0, *my_buf, *shoc_size);

	if (shoc_numread == -1)
	{
		perror("Error Printed");
		exit(EXIT_FAILURE);
	}
	else if (shoc_numread == 0)
	{
		if (isatty(0))
			_shell("\n");
		exit(EXIT_SUCCESS);
	}

	return (shoc_numread);
}
