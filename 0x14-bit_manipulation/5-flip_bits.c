#include "main.h"

/**
* flip_bits - calculates the Hamming distance between two numbers
* @n: first number
* @m: second number
*
* Return: number of differing bits
*/
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
unsigned long int difference = n ^ m;
unsigned int count = 0;

while (difference > 0)
{
count += difference & 1;
difference >>= 1;
}

return (count);

}
