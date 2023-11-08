#include "main.h"

/**
 * _strcpy - It copies a string
 * @_dest: the destination
 * @src: the source
 * Return: pointer to destination
 */

char *_strcpy(char *_dest, char *src)

{

	int a = 0;

	if (_dest == src || src == 0)

		return (_dest);

	while (src[a])

	{

		_dest[a] = src[a];

		a++;

	}

	_dest[a] = 0;

	return (_dest);

}


/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)

{

	int _length = 0;

	char *ret;

	if (str == NULL)

		return (NULL);

	while (*str++)

		_length++;

	ret = malloc(sizeof(char) * (_length + 1));

	if (!ret)

		return (NULL);

	for (_length++; _length--;)

		ret[_length] = *--str;

	return (ret);

}


/**
 *_puts - It prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)

{

	int a = 0;

	if (!str)

		return;

	while (str[a] != '\0')

	{

		_putchar(str[a]);

		a++;

	}

}


/**
 * _putchar - writes the character c to stdout
 * @_c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char _c)

{

	static int a;

	static char _buf[WRITE_BUF_SIZE];

	if (_c == BUF_FLUSH || a >= WRITE_BUF_SIZE)

	{

		write(1, _buf, a);

		a = 0;

	}

	if (_c != BUF_FLUSH)

		_buf[a++] = _c;

	return (1);

}
