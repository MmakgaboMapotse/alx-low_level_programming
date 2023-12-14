#include "main.h"

/**
* get_endianness - reveals the mysterious nature of endianness
*
* Return: 0 if big endian, 1 if little endian
*/
int get_endianness(void)
{
unsigned int magic_num = 0x0A0B0C0D;
unsigned char *byte_ptr = (unsigned char *)&magic_num;

return ((*byte_ptr == 0x0D) ? 1 : 0);

}
