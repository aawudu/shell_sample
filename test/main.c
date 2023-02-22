#include "shell.h"

/**
 * main - main entry to shell
 * @ac: number of args
 * @av: array of args
 * @env: environmental variables
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	prompt(env);

	return (0);
}
