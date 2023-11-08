#include "main.h"

/**
 * **parse - splits a string into words
 * @str: the input string to be split
 * @e: the delimeter string used for spliting
 *
 * this function splits the input string 'str' into an array of words based on
 * provided delimeter string 'e'. it counts the number of words in 'str' and
 * allocates memory for an array of strings to hold these words. each word is
 * stored as a seperate string in the returned array.
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **parse(char *str, char *e)
{
	int a, b, c, d, numwords = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!_delimeter(str[a], e) && (_delimeter(str[a + 1], e) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	r = malloc((1 + numwords) * sizeof(char *));
	if (!r)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (_delimeter(str[a], e))
			a++;
		c = 0;
		while (!_delimeter(str[a + c], e) && str[a + c])
			c++;
		r[b] = malloc((c + 1) * sizeof(char));
		if (!r[b])
		{
			for (c = 0; c < b; c++)
				free(r[c]);
			free(r);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			r[b][d] = str[a++];
		r[b][d] = 0;
	}
	r[b] = NULL;
	return (r);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string to be split
 * @e: the delimeter charater used for splitting
 *
 * this fuction split the input string into an array based the
 * provided delimeter allocates memory.
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char e)
{
	int a, b, c, d, numwords = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)/* count the no of words in str on 'e'*/
		if ((str[a] != e && str[a + 1] == e) ||
		    (str[a] != e && !str[a + 1]) || str[a + 1] == e)
			numwords++;
	if (numwords == 0)
		return (NULL);
	r = malloc((1 + numwords) * sizeof(char *));/* allocates memory */
	if (!r)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == e && str[b] != e)/* skip leading delimeter xters*/
			a++;
		c = 0;
		while (str[a + c] != e && str[a + c] && str[a + c] != e)/*count xters*/
			c++;
		r[b] = malloc((c + 1) * sizeof(char));
		if (!r[b])
		{
			for (c = 0; c < b; c++)
				free(r[c]);
			free(r);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			r[b][d] = str[a++];
		r[b][d] = 0;
	}
	r[b] = NULL;
	return (r);
}
