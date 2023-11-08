/* second part of utility part of shell program*/
#include "main.h"

/**
 * _is_atoi - converts a string to an integer by processing the xters in th str
 * @r: the string to be converted by the function _is_atoi
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _is_atoi(char *r)
{
	int a = 0;
	unsigned long int result = 0;

	if (*r == '+')
		r++;  /* TODO: why does this make main return 255? */
	for (a = 0;  r[a] != '\0'; a++)
	{
		if (r[a] >= '0' && r[a] <= '9')
		{
			result *= 10;
			result += (r[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _error - prints an error message to stderr
 * @infos: the parameter & return info struct
 * @erstr: string containing specified error message
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _error(info_t *infos, char *erstr)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(erstr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fdi: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fdi)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _xyz_, current;

	if (fdi == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_xyz_ = -input;
		__putchar('-');
		count++;
	}
	else
		_xyz_ = input;
	current = _xyz_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_xyz_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _convnum - converter function, a clone of itoa
 * @numb: number
 * @bas: base
 * @flag: argument flags
 *
 * Return: string
 */
char *_convnum(long int numb, int bas, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bas];
		n /= bas;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _remcomm - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void _remcomm(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
