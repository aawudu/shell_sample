#include "main.h"

/**
 * exe_cmd -execute command
 * @argv: pointer to array
 */

void exe_cmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;
	pid_t my_pid;

	if (argv)
	{
		command = get_location(argv[0]);

		if (command)
		{
			if (execve(command, argv, NULL) == -1)
				perror("Error:");
		}
		else
			printf("Command not found");
	}
}
