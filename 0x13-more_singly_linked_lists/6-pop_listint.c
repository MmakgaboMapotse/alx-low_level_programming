#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
	* pop_listint - Deletes the head node of a linked list.
	* @head: Pointer to the first element in the linked list.
	*
	* Return: The data inside the element that was deleted,
	*         or 0 if the list is empty.
*/
int pop_listint(listint_t **head)
{
	int data;

	if (*head == NULL)
	{
	return (0);
	}

	data = (*head)->n;
	listint_t *temp = *head;

	*head = (*head)->next;
	free(temp);

	return (data);
}
