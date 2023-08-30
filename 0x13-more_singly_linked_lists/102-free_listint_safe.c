#include "lists.h"

/**
	* free_listint_safe - Frees a listint_t list, even with loops.
	* @h: A pointer to a pointer to the head of the list.
	*
	* Return: The size of the list that was freed.
*/
size_t free_listint_safe(listint_t **h)
{
	size_t nodes = 0;
	listint_t *current = *h;

	while (current)
	{
	nodes++;

	if (current <= current->next)
	{
	*h = NULL;
	break;
	}

	listint_t *temp = current;
	(current = current->next);
	free(temp);
	}

	return (nodes);
}
