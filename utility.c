/* the below file is more of part of a uttility file to shell program*/
#include "main.h"

/**
 * active - returns true if shell is interactive mode
 * @infos:pointer to the info_t structure
 *
 * this fucntion checks if the shell is running in the interactive mode
 * Return: 1 if interactive mode, 0 otherwise
 */
int active(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
 * _is_delimeter - checks if character is a delimeter
 * @x: the char to check
 * @delim: the delimeter string
 *
 * this function checks if the character 'x' is a delimeter by comparing it
 * with the characters in the 'delim'string.
 * Return: 1 if 'x' true, 0 if false
 */
int _is_delimeter(char x, char *delim)
{
	while (*delim)
		if (*delim++ == x)
			return (1);
	return (0);
}

/**
 *_is_alpha_char - checks for alphabetic character
 *@x: The character to check
 *
 * this fuction checks if 'x' is an alphabet(A-Z or a-z)
 *Return: 1 if x is alphabetic, 0 otherwise
 */

int _is_alpha_char(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@r: the string to be converted
 *
 * the function coverts a string to an integer
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *r)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0;  r[a] != '\0' && flag != 2; a++)
	{
		if (r[a] == '-')
			sign *= -1;

		if (r[a] >= '0' && r[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (r[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
