#include "main.h"
/**
 * main - function prints input
 * @ac: takes input
 * @argv: argument value
 * Return: return 0 success, 1 error
 */
int main(int ac, char **argv)
{
	char *alert = "(heya) $";
	char *lineptr;
	size_t n = 0;

	/*prompt to enter input*/
	printf("%s", alert);
	/*reads input entered*/
	getline(&lineptr, &n, stdin);
	/*print input*/
	printf("%s\n", lineptr);

	free(lineptr);
	return (0);
}
