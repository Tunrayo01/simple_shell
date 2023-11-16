#include "my_shell.h"

/**
 * err_atoi - converts a string to an integer
 * @str: The string to be converted
 *
 * Return: Converted number if successful, -1 on error
 */
int err_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_shell_error - prints an error message from the shell
 * @info: Pointer to the ShellInfo structure
 * @error_type: String containing specified error type
 */
void print_shell_error(ShellInfo_t *info, char *error_type)
{
	_eputs(info->shell_name);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @number: The number to print
 * @fd: The file descriptor to write to
 *
 * Return: Number of characters printed
 */
int print_decimal(int number, int fd)
{
	int (*put_character)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		put_character = _eputchar;

	if (number < 0)
	{
		absolute_value = -number;
		put_character('-');
		count++;
	}
	else
		absolute_value = number;

	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			put_character('0' + current / i);
		count++;
		}
		current %= i;
	}

	put_character('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - converts a number to a string
 * @num: The number to convert
 * @base: The base for conversion
 * @flags: Argument flags
 *
 * Return: Converted string
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

do {
		*--ptr = array[n % base];
		n /= base;
	}
	while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @buffer: Address of the string to modify
 */
void remove_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

