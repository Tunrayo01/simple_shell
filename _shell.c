#include "my_shell.h"
/**
 * _shell - this is the stdout of strings to be printed
 * @shellstring: output stdout string to be used
 * Return: an integer anytime its being used
 */
int _shell(const char *shellstring)
{
	return (write(STDOUT_FILENO, shellstring, strlen(shellstring)));
}
