#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	return (st.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * dup_chars - Duplicates characters from a given range.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to the new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	char *buf = malloc(stop - start + 1);
	if (!buf)
		return (NULL);

	int i, k;
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - Finds the command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(cmd))
			return (cmd);
	}

	int i = 0, curr_pos = 0;
	char *path;

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}

	return (NULL);
}

