#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_field(const char *field_name, unsigned long value);

void check_elf(unsigned char *e_ident)
{
	if (!(e_ident[0] == ELFMAG0 && e_ident[1] == ELFMAG1 &&
	e_ident[2] == ELFMAG2 && e_ident[3] == ELFMAG3))
	{
	dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
	exit(98);
	}
}

void print_field(const char *field_name, unsigned long value)
{
	printf(" %s: %#lx\n", field_name, value);
}

int main(int argc, char *argv[])
{
	int o, r;
	Elf64_Ehdr *header = malloc(sizeof(Elf64_Ehdr));

	if (argc != 2)
	{
	dprintf(STDERR_FILENO, "Usage: %s elf_file\n", argv[0]);
	exit(98);
	}

	o = open(argv[1], O_RDONLY);
	if (o == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
	exit(98);
	}

	r = read(o, header, sizeof(Elf64_Ehdr));
	if (r == -1)
	{
	close(o);
	free(header);
	dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
	exit(98);
	}

	check_elf(header->e_ident);

	printf("ELF Header:\n");
	print_field("Magic", *(unsigned int *)header->e_ident);
	print_field("Class", header->e_ident[EI_CLASS]);
	print_field("Data", header->e_ident[EI_DATA]);
	print_field("Version", header->e_ident[EI_VERSION]);
	print_field("OS/ABI", header->e_ident[EI_OSABI]);
	print_field("ABI Version", header->e_ident[EI_ABIVERSION]);
	print_field("Type", header->e_type);
	print_field("Entry point address", header->e_entry);

	free(header);
	close(o);
	return (0);
}
