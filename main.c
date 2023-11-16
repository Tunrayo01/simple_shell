#include "my_shell.h"

/**
 * main - Entry point for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int argc, char **argv)
{
	ShellInfo_t shell_info[] = { SHELL_INFO_INIT };

	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
		 "add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error_message(argv[0]);
				print_error_message(": 0: Can't open ");
				print_error_message(argv[1]);
				put_char('\n');
				put_char(BUFFER_FLUSH);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		shell_info->read_file_descriptor = file_descriptor;
	}

	put_env_list(shell_info);
	read_history(shell_info);
	shell(shell_info, argv);
	return (EXIT_SUCCESS);
}

