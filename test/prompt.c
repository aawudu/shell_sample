#include "shell.h"

/**
 * ignore_space - trim strings
 * @str: string
 * Return: trim string
 */
char *_ignorespace(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via get_line
 * @command: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *command, list_t *env)
{
	if (i == 0) /* handles Ctrl+D */
	{
		free(command); /* exit with newline if in shell */
		free_linked_list(env);
		if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * _buildin - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int _buildin(char **token, list_t *env, int num, char **command)
{
	int i = 0;

	/* if user types "exit", free cmd tokens, and exit */
	if (_strcmp(token[0], "exit") == 0)
	{
		i = 1;
		free_double_ptr(token);
		free_linked_list(env);
		exit(0);
	}

	/* if user types "env", print, free cmd tokens, and reprompt */
	else if (_strcmp(token[0], "env") == 0)
	{
		_env(token, env);
		i = 1;
	}
	return (i);
}

/**
 * prompt -prompt user for command
 * @en: environment variables
 * Return: 0
 */
int prompt(char **en)
{
	list_t *env;
	size_t i = 0, n = 0, len;
	int command_line_no = 0, exit_stat = 0;
	char *command, *n_command, **token;

	env = env_linked_list(en);
	do {
		write(STDOUT_FILENO, "$ ", 2);
		command_line_no++;
		command = NULL;
		i = 0;
		i = _getline(&command);
		ctrl_D(i, command, env);

		n_command = command;
		command = _ignorespace(command);
		n = 0;
		while (command[n] != '\n')
			n++;
		command[n] = '\0';
		if (command[0] == '\0')
		{
			free(n_command);
			continue;
		}
		token = NULL;
		token = _strtok(command, " ");

		if (n_command != NULL)
			free(n_command);

		exit_stat = _buildin(token, env, command_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = _execmd(token, env, command_line_no);

	} while (1);
	return (exit_stat);
}
