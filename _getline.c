#include "main.h"

/**
 * my_input_buf - buffers chained commands and populates the command buffer
 * @infos: parameter struct containing information about the shell
 * @_buf: address of command buffer
 * @len: address of length of the buffer
 *
 * Return: bytes read number of bytes read from standard inputs
 */
ssize_t my_input_buf(info_t *infos, char **_buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len) /* fill whats left */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*_buf);
		*_buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(_buf, &len_p, stdin);
#else
		s = _getline(infos, _buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*_buf)[s - 1] == '\n')
			{
				(*_buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			infos->linecount_flag = 1;
			remove_comments(*_buf);
			build_history_list(infos, *_buf, infos->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = s;
				infos->cmd_buf = _buf;
			}
		}
	}
	return (s);
}

/**
 * myget_input - gets a line of newline without a trailin newline
 * @infos: parameter struct containing information about the shell
 *
 * Return: bytes read
 */
ssize_t myget_input(info_t *infos)
{
	static char *_buf; /* the ';' command chain buffer */
	static size_t a, b, len;
	ssize_t s = 0;
	char **buf_p = &(infos->arg), *q;

	_putchar(BUF_FLUSH);
	s = my_input_buf(infos, &_buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		q = _buf + a; /* get pointer for return */

		check_chain(infos, _buf, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (is_chain(infos, _buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			a = len = 0; /* reset position and length */
			infos->cmd_buf_type = CMD_NORM;
		}

		*buf_p = q; /* pass back pointer to current command position */
		return (_strlen(q)); /* return length of current command */
	}

	*buf_p = _buf; /* else not a chain, pass back buffer from _getline() */
	return (s); /* return length of buffer from _getline() */
}

/**
 * _read_buf - reads a buffer
 * @infos: parameter struct
 * @_buf: buffer
 * @a: size
 *
 * Return: s
 */
ssize_t _read_buf(info_t *infos, char *_buf, size_t *a)
{
	ssize_t s = 0;

	if (*a)
		return (0);
	s = read(infos->readfd, _buf, READ_BUF_SIZE);
	if (s >= 0)
		*a = s;
	return (s);
}

/**
 *my_getline - gets the next line of input from STDIN
 * @infos: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int my_getline(info_t *infos, char **ptr, size_t *length)
{
	static char _buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t c;
	ssize_t s = 0, r = 0;
	char *q = NULL, *new_q = NULL, *_c;

	q = *ptr;
	if (q && length)
		r = *length;
	if (a == len)
		a = len = 0;

	s = _read_buf(infos, _buf, &len);
	if (s == -1 || (s == 0 && len == 0))
		return (-1);

	_c = _strchr(_buf + a, '\n');
	c = _c ? 1 + (unsigned int)(_c - _buf) : len;
	new_q = _realloc(q, r, r ? r + c : c + 1);
	if (!new_q) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (r)
		_strncat(new_q, _buf + a, c - a);
	else
		_strncpy(new_q, _buf + a, c - a + 1);

	r += c - a;
	a = c;
	q = new_q;

	if (length)
		*length = r;
	*ptr = q;
	return (r);
}

/**
 * _sigintHandler - blocks ctrl-C
 *
 * @sig_num: the signal number
 *
 * Return: void
 */
void _sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");

	_puts("Ogu_Majam===>$ ");
	_putchar(BUF_FLUSH);
}
