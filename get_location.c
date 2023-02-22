#include "main.h"

/**
 * get_location -get location of exec cmd
 * @command: cmd
 * Return: location to cmd or cmd
 */

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path); /* Duplicate the path string */
		command_length = strlen(command); /* get len of command */
		path_token = strtok(path_copy, ":"); /*break path and get all dir available*/
		while (path_token != NULL)
		{
			directory_length = strlen(path_token); /* get len of directory */
			file_path = malloc(command_length + directory_length + 2); /*allocate memo*/

			/*concat command to file path*/
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0) /*test if file exists */
			{
				free(path_copy); /*free mem for copy created*/
				return (file_path); /* return file path */
			}
			else
			{
				free(file_path); /* free mem for path to check another path */
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy); /* free mem for path if path doesn't exist */
		if (stat(command, &buffer) == 0) /* check if command is a file_path */
			return (command);
		return (NULL);
	}
	return (NULL);
}
