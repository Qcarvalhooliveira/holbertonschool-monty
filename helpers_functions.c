#include "monty.h"
/**
 * pall - print all elements of stack.
 * @stack: pointer head stack.
 * @line_number: files line number.
 * Return: the number of nodes.
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *h = *stack;
	(void)line_number;
	while (h != NULL)
	{
		printf("%i\n", h->n);
		h = h->next;
	}
}

/**
 * push - Implement the pint opcode.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: nothing.
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *node = NULL;
	stack_t *copy = *stack;
	(void)line_number;

	if (stack == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		var_glob[1] = 1;
		return;
	}
	node = malloc(sizeof(stack_t));
	if (node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(stack);
		var_glob[1] = 1;
		return;
	}
	node->prev = NULL;
	node->n = var_glob[0];
	node->next = *stack;
	if (*stack)
		copy->prev = node;
	*stack = node;
}
/**
 * pint - Implement the pint opcode.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: nothing.
 */

void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		var_glob[1] = 1;
		return;
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - remove a element to the top of stack.
 * @stack: pointer to head of stack.
 * @line_number: files line number.
 * Return: void.
 */

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *node = *stack;

	if ((*stack) == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free(stack);
		var_glob[1] = 1;
		return;
	}
	if (node)
	{

		*stack = (node)->next;
		free(node);
	}
}

/**
 * swap - swap two element in stack.
 * @stack: pointer to head of stack.
 * @line_number: files line number.
 * Return: void.
 */

void swap(stack_t **stack, unsigned int line_number)
{
	int i, j = 0;
	stack_t *copy_stack = *stack;

	while (copy_stack != NULL)
	{
		i++;
		copy_stack = copy_stack->next;
	}
	if (i < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		free(stack);
		var_glob[1] = 1;
		return;
	}
	j = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = j;
}
