#include "main.h"

/**
 * _is_cmd - determines if a file is an executable command
 * @infos: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _is_cmd(info_t *infos, char *path)
{
	struct stat st;

	(void)infos;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupchars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @_stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupchars(char *path_str, int start, int _stop)
{
	static char buf[1024];
	int a = 0, c = 0;

	for (c = 0, a = start; a < _stop; a++)
		if (path_str[a] != ':')
			buf[c++] = path_str[a];
	buf[c] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @infos: the info struct
 * @path_str: the PATH string
 * @_cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *infos, char *path_str, char *_cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
		if (_is_cmd(infos, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!path_str[a] || path_str[a] == ':')
		{
			path = dupchars(path_str, curr_pos, a);
			if (!*path)
				_strcat(path, _cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, _cmd);
			}
			if (_is_cmd(infos, path))
				return (path);
			if (!path_str[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
