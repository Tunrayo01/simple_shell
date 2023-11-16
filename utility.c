#include "my_shell.h"

/**
 * is_shell_active - checks if the shell is in interactive mode
 * @info: Pointer to the ShellInfo structure
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_shell_active(ShellInfo_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_file_descriptor <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @character: The character to check
 * @delimiters: The string of delimiters
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char character, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == character)
			return (1);
	return (0);
}

/**
 * is_alpha_character - checks if a character is alphabetic
 * @character: The character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int is_alpha_character(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - converts a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int string_to_integer(char *str)
{
	int i, sign = 1, flag = 0, result;
	unsigned int output = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	result = (sign == -1) ? -output : output;

	return (result);
}
