#include "my_shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(shellInfo_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

			if (!*len) /* if nothing left in the buffer, fill it */
	{
		free_memory(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
			r = shell_getline(info, buf, &len_p);
	#endif
		if (r > 0)
		{
		if ((*buf)[r - 1] == '\n')
			{
					(*buf)[r - 1] = '\0'; /* remove trailing newline */
					r--;
			}
				info->line_count_flag = 1;
				remove_comments(*buf);
				build_history_list(info, *buf, info->history_count++);
		/* if (is_command_chain(info, *buf, &r)) is this a command chain? */
			{
				*len = r;
				info->command_buffer = buf;
			}
			}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(shellInfo_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	put_char(BUFFER_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_command_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_command_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->command_buffer_type = COMMAND_NORMAL;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (string_length(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from shell_getline() */
	return (r);    /* return length of buffer from shell_getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(shellInfo_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->read_file_descriptor, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * shell_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int shell_getline(shellInfo_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = starts_with(buf + i, "\n");
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free_memory(p), -1 : -1);

	if (s)
		string_concat_n(new_p, buf + i, k - i);
	else
		string_copy_n(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_sigint - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
	put_char('\n');

	print_string("Ogu_Majam===>$ ");
	put_char(BUFFER_FLUSH);
}

