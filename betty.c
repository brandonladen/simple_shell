#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

int execute_command(char **args);
char **parse_arguments(char *line);
int launch_process(char **args);
int check_builtin_commands(char **args);
char *read_line(void);

int main(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("($) ");
        line = read_line();
        args = parse_arguments(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);

    return 0;
}

int execute_command(char **args)
{
    if (args[0] == NULL) {
        return 1;  // Empty command, continue prompt
    }

    if (check_builtin_commands(args)) {
        return 1;  // Builtin command executed, continue prompt
    }

    return launch_process(args);
}

char **parse_arguments(char *line)
{
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char **args = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!args) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL) {
        args[position] = token;
        position++;

        if (position >= buffer_size) {
            buffer_size += BUFFER_SIZE;
            args = realloc(args, buffer_size * sizeof(char *));
            if (!args) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITERS);
    }
    args[position] = NULL;
    return args;
}

int launch_process(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror(args[0]);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Forking error");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int check_builtin_commands(char **args)
{
    if (strcmp(args[0], "exit") == 0) {
        return 0;  // Exit command, terminate shell
    }

    return 0;
}

char *read_line(void)
{
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char *buffer = malloc(buffer_size * sizeof(char));
    int c;

    if (!buffer) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }

        position++;

        if (position >= buffer_size) {
            buffer_size += BUFFER_SIZE;
            buffer = realloc(buffer, buffer_size * sizeof(char));
            if (!buffer) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }
    }
}

