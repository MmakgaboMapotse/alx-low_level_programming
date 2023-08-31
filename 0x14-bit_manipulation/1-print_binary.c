#include "main.h"

/**
	* print_binary - prints the binary equivalent of a decimal number
	* @n: number to print in binary
*/
void print_binary(unsigned long int n)
{
	if (n == 0)
	{
	_putchar('0');
	return;
	}

	int started = 0;

	for (int i = 63; i >= 0; i--)
	{
	if (n & (1UL << i))
	{
	_putchar('1');
	started = 1;
	}
	else if (started)
	{
	_putchar('0');
	}
	}
}
