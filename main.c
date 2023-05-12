#include "monty.h"

/**
 *lines_check - check line to arguments
 *@buffer: contain all
 *@line_number: count to lines inside the file
 *Return: Tokens
 */

char *lines_check(char *buffer, unsigned int line_number)
{
	char *token = NULL, *num_t = NULL;
	long int i = 0;

	token = strtok(buffer, " \t\n");
	if (strcmp(token, "push") == 0)
	{
		num_t = strtok(NULL, " \t\n");
		if (num_t == NULL)
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			free(buffer);
			var_glob[1] = 1;
			return (NULL);
		}
		for (i = 0; num_t[i] != '\0'; i++)
		{
			if (num_t[i] == '-')
				i++;
			if (num_t[i] < 48 || num_t[i] > 57)
			{
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				free(buffer);
				var_glob[1] = 1;
				return (NULL);
			}
		}
		var_glob[0] = atoi(num_t);
	}
	return (token);
}

/**
 *main - execute the monty interpreter
 *@argc: count number to arguments per line
 *@argv: array to arguments
 *Return: 0 if no exist or exit failure in case to error
 */

int main(int argc, char *argv[])
{
	stack_t *stack = NULL;
	FILE *file;
	char *buffer = NULL, *command_f = NULL;
	size_t size = 0;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&buffer, &size, file) != EOF)
	{
		line_number++;
		if (strlen(buffer) == 1 || strspn(buffer, " \t\n") == strlen(buffer))
			continue;
		command_f = lines_check(buffer, line_number);
		if (command_f == NULL)
			break;
		functions_monty(&stack, command_f, line_number);
	}
	free(buffer);
	free_malloc(stack);
	fclose(file);
	if (var_glob[1] == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
