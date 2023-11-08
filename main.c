#include "main.h" /* main library of the header files */

/**
 * main - entry point
 * @bc: arg count
 * @bv: arg vector
 *
 * Return: 0 , 1 for error
 */

int main(int bc, char **bv)
{
	/* Initialize info_t structure*/

	info_t info[] = { INFO_INIT };

	int fd = 2;

	asm ("mov %1, %0\n\t"/* Inline assembly to modify 'fd'*/

		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
	if (bc == 2)
	{
/* Open the file specified in the command-line argument*/
		fd = open(bv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(bv[0]);
				_eputs(": 0: Can't open ");
				_eputs(bv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
/*  Set 'readfd' in the 'info' structure to the opened file descriptor*/
		info->readfd = fd;
	}
	/* Perform shell-related operation*/
	put_env_list(info);
	read_history(info);
	hsh(info, bv);
	return (EXIT_SUCCESS);

}
