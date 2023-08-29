#include <stdio.h>
#include "lists.h"

size_t print_listint(const listint_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
	printf("%d", h->n);

	if (h->next != NULL)
	{
	printf(", ");
	}
	else
	{
		printf(" -> ");
	}

	h = h->next;
	count++;
	}

	printf("%lu element%s\n", count, count == 1 ? "" : "s");

	return (count);
}
