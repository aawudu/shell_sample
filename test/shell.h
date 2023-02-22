#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - linked list for environmental variables
 * @var: environmental variable
 * @next: pointer to next node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;

int prompt(char **env);
size_t _getline(char **str);
int _execmd(char **s, list_t *env, int num);
char **_strtok(char *str, char *delm);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
list_t *env_linked_list(char **env);
list_t *add_end_node(list_t **head, char *str);
size_t print_list(list_t *h);
void free_linked_list(list_t *list);
void free_double_ptr(char **str);
int _strcmp(char *s1, char *s2);
int _env(char **str, list_t *env);

#endif
