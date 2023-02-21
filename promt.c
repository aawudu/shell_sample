#include "main.h"

/**
 * prompt -prompt the user for command
 * Return: (status)
 */

int prompt()
{
	char *command = NULL;
	char *token;
	const char *delim = " \n";
	int i, status;

	size_t len = 0;
	ssize_t n_chars;
	pid_t child_pid;

	while (1)
	{
		printf("prompt $ ");
		n_chars = getline(&command, &len, stdin);

		token = strtok(command, delim); /*spit command to token*/
		char **arr = malloc(sizeof(char *) * n_chars); /* allocate mem for tokens*/
		arr[0] = token; /* get first token */

		i = 1;
		while (token != NULL) /* getting the rest of tokens to array */
		{
			token = strtok(NULL, delim);
			arr[i] = token;
			i++;
		}

		child_pid = fork(); /*create another process*/
		if (child_pid == -1)
		{
			perror("Error");
			return (-1);
		}
		else if (child_pid == 0)
			execve(arr[0], arr, NULL);
		else
			wait(&status);
	}

	free(command);
	return (0);
}
