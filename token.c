#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
/**
 * tokenizer - Checks the code
 *
 * Return: 0
 */
int tokenizer(char *string)
{
	char *token = strtok(string, " ");
	char *argv[5];
	int status, i = 0;
	pid_t child_pid;

	if (strcmp(string, "exit") == 0)
	{
		exit(0);
	}

	child_pid = fork();

	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	if (child_pid == -1)
	{
		perror("Error");
	}

	if (child_pid == 0)
	{
		if (strcmp(argv[0], "ppid") == 0)
		{
			printf("%d\n", getppid());
			exit(0);
		}
	
		if (execvp(argv[0], argv) == -1)
		{
			perror("Brandon Error");
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
