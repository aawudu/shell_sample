#include "shell.h"

/**
 * c_strdup - custom string duplication; excludes beginning bytes
 * @str: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @cs: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *c_strdup(char *str, int cs)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);

	/* calculate len + null terminator to malloc */
	while (*(str + len))
		len++;
	len++;

	/* allocate memory but exclude environmental variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - cs));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (len - cs))
	{
		*(duplicate_str + i) = *(str + cs + i);
		i++;
	}
	return (duplicate_str);
}

/**
 * get_env - finds and returns a copy of the requested environmental variable
 * @str: string to store it in
 * @env: entire set of environmental variables
 * Return: copy of requested environmental variable
 */
char *get_env(char *str, list_t *env)
{
	int j = 0, cs = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0' && (env->var)[j] == '=')
			break;
		env = env->next;
	}

	while (str[cs] != '\0') /* find how many bytes in env variable title */
		cs++;
	cs++; /*counts 1 more for = sign*/
	return (c_strdup(env->var, cs)); /* make a copy of variable w/o title */
}

/**
 * _getlocation - append command to locations/path
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * @env: environmental variable
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *_getlocation(char *str, list_t *env)
{
	char *pth, *cat = NULL, **tokens;
	int i = 0;

	/* get and tokenize PATH directories, then free original string */
	pth = get_env("PATH", env);
	tokens = _strtok(pth, ":");
	free(pth);

	/* append "/cmd" to each token to see it's legit */
	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = _strdup(tokens[i]);
		cat = _strcat(cat, "/");
		cat = _strcat(cat, str);
		if (access(cat, F_OK) == 0)
		{
			/* free tokens before returning legit fleshed path */
			free_double_ptr(tokens);
			return (cat);
		}
		free(cat); /* free concatenated string if cmd is never found */
		i++;
	}
	free_double_ptr(tokens);
	return (str); /* return string if not found; won't pass execve */
}

/**
 * _execmd - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int _execmd(char **s, list_t *env, int num)
{
        char *holder;
        int status = 0, t = 0;
        pid_t pid;

        /* check if command is absolute path */
        if (access(s[0], F_OK) == 0)
        {
                holder = s[0];
                t = 1;
        }
        /* else flesh out full path */
        else
                holder = _getlocation(s[0], env);
        /* if not an executable, free */
        if (access(holder, X_OK) != 0)
        {
               perror("Error:");
                free_double_ptr(s);
                return (127);
        }
        else /* else fork and execute executable command */
        {
                pid = fork();
                if (pid == 0) /* if child process, execute */
                {
                        if (execve(holder, s, NULL) == -1)
                        {
                                perror("Error:");
                                free_double_ptr(s);
                                free_linked_list(env);
                                exit(0);
                        }
                }
                else /* if parent, wait for child then free all */
                {
                        wait(&status);
                        free_double_ptr(s);
                        if (t == 0)
                                free(holder);
                }
        }
        return (0);
}
