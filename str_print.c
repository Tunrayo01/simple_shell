#include "main.h"


/**
 **_strncpy - copies a string
 *@_dest: the destination string to be copied to
 *@src: the source string
 *@_n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *_dest, char *src, int _n)

{

	int a, b;

	char *z = _dest;



	a = 0;

	while (src[a] != '\0' && a < _n - 1)

	{

		_dest[a] = src[a];

		a++;

	}

	if (a < _n)

	{

		b = a;

		while (b < _n)

		{

			_dest[b] = '\0';

			b++;

		}

	}

	return (z);

}



/**
 **_strncat - concatenates two strings
 *@_dest: the first string
 *@src: the second string
 *@_n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strncat(char *_dest, char *src, int _n)

{

	int a, b;

	char *z = _dest;

	a = 0;
	b = 0;

	while (_dest[a] != '\0')

		a++;
	while (src[b] != '\0' && b < _n)

	{

		_dest[a] = src[b];
		a++;
		b++;

	}

	if (b < _n)

		_dest[a] = '\0';

	return (z);

}

/**
 **_strchr - locates a character in a string
 *@z: the string to be parsed
 *@_c: the character to look for
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *z, char _c)

{

	do {
		if (*z == _c)

			return (z);

	} while (*z++ != '\0');

	return (NULL);

}
