#include "main.h"
/**
 * main - prints input
 * @argc: inputs
 * @argv: argument value
 * Return: return 0 success
 */
int main(int argc, char **argv)
{
	char *prompt = "(Say) $";
	/* getline args */
	char *lineptr;
	size_t n = 0;
	/* prompt for user input */
	printf("%s", prompt);
	/* reading and getting what user types with getline*/
	getline(&lineptr, &n, stdin);
	printf("%s\n", lineptr);
	free(lineptr);
	return (0);
}
