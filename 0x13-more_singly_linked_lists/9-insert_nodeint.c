#include "lists.h"

listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n)
{
	if (!head)
		return (NULL);

	listint_t *new = malloc(sizeof(listint_t));
	if (!new)
		return (NULL);

	new->n = n;

	if (idx == 0)
	{
	new->next = *head;
	*head = new;
	return (new);
	}

	listint_t *current = *head;
	for (unsigned int i = 0; current && i < idx - 1; i++)
	current = current->next;

	if (!current)
	{
	free(new);
	return (NULL);
	}

	new->next = current->next;
	current->next = new;

	return (new);
}
