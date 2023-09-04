#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/**
	* print_error - prints an error message to stderr and exits with status code 98
	* @message: error message to display
*/
void print_error(char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(98);
}

/**
	* print_elf_header_info - displays information from the ELF header
	* @header: pointer to the ELF header
*/
void print_elf_header_info(Elf64_Ehdr *header)
{

	printf(" Magic: ");
	for (int i = 0; i < EI_NIDENT; i++)

	{
	printf("%02x", header->e_ident[i]);
	if (i < EI_NIDENT - 1)
	printf(" ");
	}
	printf("\n");
	printf("  Class:				%s\n", header->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");
	printf("  Data:	%s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
	printf("  Version:				%d (current)\n", header->e_ident[EI_VERSION]);
	printf("  OS/ABI:				%s\n", header->e_ident[EI_OSABI] == ELFOSABI_SYSV ? "UNIX - System V" : "Unknown");
	printf("  ABI Version:				%d\n", header->e_ident[EI_ABIVERSION]);
	printf("  Type:					%s\n", header->e_type == ET_EXEC ? "EXEC (Executable file)" :
							header->e_type == ET_DYN ? "DYN (Shared object file)" :
							header->e_type == ET_REL ? "REL (Relocatable file)" : "Unknown");
	printf("  Entry point address:			0x%lx\n", (unsigned long)header->e_entry);
}

int main(int argc, char *argv[])
{
	int fd;
	Elf64_Ehdr elf_header;

	if (argc != 2)
	print_error("Usage: elf_header elf_filename");

	fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	print_error("Error: Cannot open file");

	if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
	print_error("Error: Cannot read ELF header");

	if (lseek(fd, 0, SEEK_SET) == -1)
	print_error("Error: Cannot reset file offset");

	if (elf_header.e_ident[EI_MAG0] != ELFMAG0 || elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
	elf_header.e_ident[EI_MAG2] != ELFMAG2 || elf_header.e_ident[EI_MAG3] != ELFMAG3)
	print_error("Error: Not an ELF file");

	print_elf_header_info(&elf_header);

	close(fd);

	return (0);
}
