#include "main.h"

/**
 * get_user_history_file - Get the file path for storing user's shell history.
 * @user_info: Parameter struct containing user-specific information.
 *
 * This function constructs and returns the file path for storing the user's
 * shell history.
 *
 * Return: Allocated string containing the history file path or NULL on
 * failure.
 */
char *get_user_history_file(info_t *user_info)
{
	char *path_buffer, *user_home;

	user_home = get_env(user_info, "HOME=");
	if (!user_home)
		return (NULL);
	path_buffer = malloc(sizeof(char) * (_strlen(user_home) +
				_strlen(HIST_FILE) + 2));
	if (!path_buffer)
		return (NULL);
	path_buffer[0] = 0;
	_strcpy(path_buffer, user_home);
	_strcat(path_buffer, "/");
	_strcat(path_buffer, HIST_FILE);
	return (path_buffer);
}

/**
 * write_user_history - Write the user's shell history to a file.
 * @user_info: Parameter struct containing user-specific information.
 *
 * This function creates a file or appends to an existing
 * history file and writes
 * the user's shell history to it.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_user_history(info_t *user_info)
{
	ssize_t file_descriptor;
	char *file_path = get_user_history_file(user_info);
	list_t *history_node = NULL;

	if (!file_path)
		return (-1);

	file_descriptor = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_path);
	if (file_descriptor == -1)
		return (-1);
	for (history_node = user_info->history; history_node;
			history_node = history_node->next)
	{
		_putsfd(history_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_user_history - Read the user's shell history from a file.
 * @infos: Parameter struct containing user-specific information
 *
 * This function reads the user's shell history from a file and populates
 * the history list.
 *
 * Return: The new history count on success, 0 on failure.
 */
int read_user_history(info_t *infos)
{
	int a, last_index = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *file_path = get_user_history_file(infos);

	if (!file_path)
		return (0);

	file_descriptor = open(file_path, O_RDONLY);
	free(file_path);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stats))
		file_size = file_stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (a = 0; a < file_size; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(infos, buffer + last_index,
					line_count++);
			last_index = a + 1;
		}
	if (last_index != a)
		build_history_list(infos, buffer + last_index, line_count++);
	free(buffer);
	infos->histcount = line_count;
	while (infos->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infos->history), 0);
	renumber_history(infos);
	return (infos->histcount);
}

/**
 * add_to_user_history_list - Add an entry to the user's history linked list.
 * @infos:  Parameter struct containing user-specific information.
 * @buffer: Buffer containing the command history.
 * @line_count: The history line count (hist_count).
 *
 * This function adds an entry to the user's history linked list.
 *
 * Return: Always 0.
 */
int add_to_user_history_list(info_t *infos, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (infos->history)
		node = infos->history;
	add_node_end(&node, buffer, line_count);

	if (!infos->history)
		infos->history = node;
	return (0);
}

/**
 * renumber_user_history - Renumber the user's history linked list
 * after changes.
 * @infos: Parameter struct containing user-specific information.
 *
 * This function renumbers the user's history linked list after
 * changes have been made.
 *
 * Return: The new history count (hist_count).
 */
int renumber_user_history(info_t *infos)
{
	list_t *node = infos->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (infos->histcount = a);
}
