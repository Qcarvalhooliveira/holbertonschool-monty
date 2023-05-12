#include "monty.h"

/**
 *  * main - Entry point for the monty interpreter.
 *   *
 *    * @argc: number of arguments
 *     * @argv: array of arguments
 *      *
 *       * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 *        */
int main(int argc, char **argv)
{
	FILE *file;
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t read = 0;
	char *command_f = NULL;
	stack_t *stack = NULL;
	unsigned int line_number = 0;
	int operation_successful = 0;

	var_glob[1] = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while ((read = getline(&buffer, &bufsize, file)) != -1)
	{
		line_number++;
		command_f = strtok(buffer, "\n\t\r ");

		if (command_f == NULL || command_f[0] == '#')
			continue;

		if (strcmp(command_f, "push") == 0)
		{
			command_f = strtok(NULL, "\n\t\r ");

			if (command_f == NULL || is_numeric(command_f) == 0)
			{
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				free(buffer);
				free_malloc(stack);
				fclose(file);
				return (EXIT_FAILURE);
			}

			push(&stack, atoi(command_f));
			operation_successful = 1;
		}
		else if (strcmp(command_f, "pall") == 0)
		{
			pall(&stack, line_number);
			operation_successful = 1;
		}
		else
		{
			functions_monty(&stack, command_f, line_number);
			operation_successful = 1;
		}

		if (!operation_successful)
		{
			fprintf(stderr, "Error: Failed to execute operation at line %u\n", line_number);
			free(buffer);
			free_malloc(stack);
			fclose(file);
			return (EXIT_FAILURE);
		}
	}

	free(buffer);
	free_malloc(stack);
	fclose(file);
	return (EXIT_SUCCESS);
}
