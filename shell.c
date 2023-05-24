#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
/**
 * main - Checks the code
 *
 * Return: 0
 */
extern char **environ;
int main(int ac, char **av)
{
        FILE *stream;
        char *line = NULL; // initialize line to NULL
        size_t len = 0;
        ssize_t nread;
	char **env = environ;

        stream = stdin; // use standard input

        printf("My_shell~ ");
        while ((nread = getline(&line, &len, stream)) != -1)
        {
		if (nread == 0 || (nread == 1 && line[0] == '\n'))
		{
			continue;
		}
		if (line[nread-1] == '\n')
		{
			line[nread-1] = '\0';

		}
		if (strcmp(line, "env") == 0)
		{
			while (*env)
			{
				printf("%s\n", *env++);
			}
		}
		else 
		{
			tokenizer(line);
		}
		printf("My_shell~ ");
	}

        free(line); // free the memory allocated by getline

        return (EXIT_SUCCESS);
}
