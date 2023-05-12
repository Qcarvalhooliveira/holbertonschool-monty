#include "monty.h"

int is_numeric(char *str)
{
	int i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	for (; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
			return (0);
	}
	return (1);
}
