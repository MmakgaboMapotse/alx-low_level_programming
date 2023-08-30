#include "lists.h"

/**
	* reverse_listint - reverses a linked list
	* @head: pointer to the first node in the list
	*
	* Return: pointer to the first node in the new reversed list
*/

listint_t *reverse_listint(listint_t **head)
{
	listint_t *prev = NULL;

	while (*head)
	{
	listint_t *next = (*head)->next;
	(*head)->next = prev;
	prev = *head;
	*head = next;
	}

	return (prev);
}
