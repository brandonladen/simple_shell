#ifndef _SHELL_H_
#define _SHELL_H_

/** declared external variable **/
extern char **environment;

/** defines macros for read/write **/
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH_FLAG -1

/** headers for commonly used libraries **/
#include <stdio.h> /** standard input/output functions **/
#include <unistd.h> /** various system calls **/
#include <sys/types.h> /** Defines various different datatypes**/
#include <string.h> /** string manupulation function**/
#include <sys/wait.h> /** process wait and termination functions **/
#include <stdlib.h> /**general utilities, including memory allocation functions.**/
#include <signal.h> /** signal handling function s**/
#include <sys/stat.h> /** file status functions**/
#include <fcntl.h> /** file control options and functions**/
#include <errno.h> /** error handling and reporting**/
#include <limits.h> /** constans for system limits **/

/** STRING FUNCTION **/

char *tokenize_string(char *str, const char *delimiter);
unsigned int check_delimiter(char character, const char *delimiter_str);
char *copy_string(char *destination, char *source, int num_chars);
int calculate_string_length(char *str);
int print_character(char c);
int convert_string_to_integer(char *str);
void print_string(char *str);
int compare_strings(char *string1, char *string2);
int check_if_alpha(int c);
void reverse_array(char *arr, int length);
int calculate_integer_length(int num);
char *convert_integer_to_string(unsigned int n);
char *concatenate_strings(char *dest, char *src);
char *copy_string(char *dest, char *src);
char *find_character(char *s, char c);
int compare_strings(const char *s1, const char *s2);
char *duplicate_string(char *str);

/**  MEMORY MANAGEMENT **/

void free_environment(char **env);
void *fill_array(void *array, int element, unsigned int length);
char *memory_copy(char *dest, char *src, unsigned int num_bytes);
void *allocate_memory(unsigned int size);
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all_resources(char **input, char *line);

/** INPUT FUNCTION **/

void display_prompt(void);
void handle_signal(int sig);
char *get_input_line(void);

/** COMMAND PARSER AND EXTRACTOR **/

int handle_path_command(char **line);
char *get_environment_variable(char *name);
char **parse_command(char *cmd);
int handle_builtin_command(char **cmd, int error);
void read_file_contents(char *filename, char **argv);
char *build_string(char *token, char *value);
int check_builtin_command(char **cmd);
void create_environment(char **env);
int check_command(char **tokens, char *line, int count, char **argv);
void process_file(char *line, int counter, FILE *fd, char **argv);
void exit_builtin_for_file(char **cmd, char *line, FILE *fd);

/** BUILTIN FUNCTIONS **/

void handle_hashtags(char *buffer);
int handle_history(char *input);
int display_history(char **cmd, int error);
int display_environment(char **cmd, int error);
int change_directory(char **cmd, int error);
int display_help_info(char **cmd, int error);
int execute_echo_command(char **cmd, int error);
void exit_builtin(char **cmd, char *input, char **argv, int count);
int print_echo_output(char **cmd);

/** ERROR HANDLING AND PRINTER **/
void print_unsigned_number(unsigned int n);
void print_integer(int n);
void print_error_message(char *line, int count, char **argv);
void print_error(char **argv, int count, char **cmd);


/**
 *  * struct builtin_command - Contains a builtin command and its corresponding function to execute
 *   * @command: Pointer to a character
 *    * @function: Function to execute when the builtin command is matched
 *     */

typedef struct  builtin_command
{
		char *command;
			int (*function)(char **line, int error);
} builtin_command_t;
#endif

