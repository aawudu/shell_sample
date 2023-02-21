#include "main.h"

/**
 * exe_cmd -execute command
 * @argv: pointer to array
 */

void exe_cmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv)
	{
		if (execve(argv[0], argv, NULL) == -1)
			perror("Error:");
	}
}
