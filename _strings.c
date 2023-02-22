#include "main.h"

/**
 * _strlen -return len of string
 * @s: string array
 * Return: length of s
 */

int _strlen(char *s)
{
	int i, len;

	if (*s == '\0')
		len = 0;
	else
	{
		for (i = 0; s[i] != 0; i++)
			len = i + 1;
	}
	return (len);
}


/**
 * _strcmp -compares two strings
 * @a: first string
 * @b: second string
 * Return: 0 if false and 1 for true
 */

int _strcmp(char *a, char *b)
{
	int i = 0;
	
	while (b[i] != '\0' || a[i] != '\0')
	{
		if (a[i] !=  b[i])
			return (1);
		i++;
	}

	return (0);
}
