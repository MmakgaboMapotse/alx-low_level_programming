#include "main.h"

/**
* binary_to_uint - converts a binary number to unsigned int
* @b: string containing the binary number
*
* Return: the converted number, or 0 if input is invalid
*/
unsigned int binary_to_uint(const char *b)
{
unsigned int dec_val = 0;
int i;

if (!b)
return (0);

for (i = 0; b[i] != '\0'; i++)
{
if (b[i] != '0' && b[i] != '1')
return (0);
}

for (i = 0; b[i] != '\0'; i++)
{

dec_val = (dec_val << 1) | (b[i] - '0');
}

return (dec_val);

}
