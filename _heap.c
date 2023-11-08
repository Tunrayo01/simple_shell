#include "main.h"

/**
 **my_memset - fills memory with a constant byte
 *@z: the pointer to the memory area
 *@y: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *my_memset(char *z, char y, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		z[a] = y;
	return (z);
}

/**
 * _ffree - frees a string of strings
 * @qq: string of strings
 */
void _ffree(char **qq)
{
	char **x = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(x);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @my_old_size: byte size of previous block
 * @my_new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int my_old_size, unsigned int my_new_size)
{
	char *q;

	if (!ptr)
		return (malloc(my_new_size));
	if (!my_new_size)
		return (free(ptr), NULL);
	if (my_new_size == my_old_size)
		return (ptr);

	q = malloc(my_new_size);
	if (!q)
		return (NULL);

	my_old_size = my_old_size < my_new_size ? my_old_size : my_new_size;
	while (my_old_size--)
		q[my_old_size] = ((char *)ptr)[my_old_size];
	free(ptr);
		return (q);
}


/**
 * _bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int _bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
