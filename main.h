#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int _strcmp(char a[], char b[]);
int prompt();
char *get_location(char *command);
void exe_cmd(char **argv);

#endif
