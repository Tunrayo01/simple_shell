#include "main.h"


/**
 * _strlen - This returns the length of a string
 * @z: the string whose length to check
 * Return: integer length of string
 */

int _strlen(char *z)

{

	int a;

	a = 0;

	while (*z != '\0')

	{

		a++;

		z++;

	}

	return (a);

}



/**
 * _strcmp -This performs lexicogarphic comparison of two strangs.
 * @z1: the first strang
 * @z2: the second strang
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int _strcmp(char *z1, char *z2)

{

	int a = 0;

	while (*(z1 + a) == *(z2 + a) && *(z1 + a))

		a++;

	if (*(z2 + a))

		return (*(z1 + a) - *(z2 + a));

	else

		return (0);

}

/**
 * starts_with - This checks if needle starts with haystack
 * @_haystack: string to search
 * @_needle: the substring to find
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *_haystack, const char *_needle)

{

	while (*_needle)

		if (*_needle++ != *_haystack++)

			return (NULL);

	return ((char *)_haystack);

}


/**
 * _strcat - concatenates two strings
 * @_dest: the destination buffer
 * @src: the source buffer
 *
 * Return: The pointer to destination buffer
 */

char *_strcat(char *_dest, char *src)

{
	char *ret = _dest;

	while (*_dest)

		_dest++;

	while (*src)

		*_dest++ = *src++;

	*_dest = *src;

	return (ret);

}
