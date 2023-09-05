#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic_numbers(unsigned char *e_ident);
void print_class_info(unsigned char *e_ident);
void print_data_encoding(unsigned char *e_ident);
void print_version_info(unsigned char *e_ident);
void print_os_abi(unsigned char *e_ident);
void print_abi_version(unsigned char *e_ident);
void print_file_type(unsigned int e_type, unsigned char *e_ident);
void print_entry_point(unsigned long int e_entry, unsigned char *e_ident);
void close_file(int file_descriptor);

/**
 * check_elf - Checks if a file is in ELF format.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: Exits with error code 98 if the file is not in ELF format.
 */
void check_elf(unsigned char *e_ident)
{
	int index;
	for (index = 0; index < 4; index++)
	{
	if (e_ident[index] != 127 &&
	e_ident[index] != 'E' &&
	e_ident[index] != 'L' &&
	e_ident[index] != 'F')
	{
	dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
	exit(98);
	}
	}
}

/**
 * print_magic_numbers - Prints the magic numbers of an ELF header.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void print_magic_numbers(unsigned char *e_ident)
{
	int index;
	printf(" Magic: ");

	for (index = 0; index < EI_NIDENT; index++)
	{
	printf("%02x", e_ident[index]);

	if (index == EI_NIDENT - 1)
	printf("\n");
	else
	printf(" ");
	}
	}

/**
 * print_class_info - Prints the class information of an ELF header.
 * @e_ident: A pointer to an array containing the ELF class information.
 */
void print_class_info(unsigned char *e_ident)
{
	printf(" Class: ");

	switch (e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
	printf("none\n");
	break;
	case ELFCLASS32:
	printf("ELF32\n");
	break;
	case ELFCLASS64:
	printf("ELF64\n");
	break;
	default:
	printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_data_encoding - Prints the data encoding of an ELF header.
 * @e_ident: A pointer to an array containing the ELF data encoding.
 */
void print_data_encoding(unsigned char *e_ident)
{
	printf(" Data: ");

	switch (e_ident[EI_DATA])
	{
	case ELFDATANONE:
	printf("none\n");
	break;
	case ELFDATA2LSB:
	printf("2's complement, little endian\n");
	break;
	case ELFDATA2MSB:
	printf("2's complement, big endian\n");
	break;
	default:
	printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_version_info - Prints the version information of an ELF header.
 * @e_ident: A pointer to an array containing the ELF version information.
 */
void print_version_info(unsigned char *e_ident)
{
	printf(" Version: %d",
	e_ident[EI_VERSION]);

	switch (e_ident[EI_VERSION])
	{
	case EV_CURRENT:
	printf(" (current)\n");
	break;
	default:
	printf("\n");
	break;
	}
}

/**
 * print_os_abi - Prints the OS/ABI of an ELF header.
 * @e_ident: A pointer to an array containing the ELF OS/ABI information.
 */
void print_os_abi(unsigned char *e_ident)
{
	printf(" OS/ABI: ");

	switch (e_ident[EI_OSABI])
	{
	case ELFOSABI_NONE:
	printf("UNIX - System V\n");
	break;
	case ELFOSABI_HPUX:
	printf("UNIX - HP-UX\n");
	break;
	case ELFOSABI_NETBSD:
	printf("UNIX - NetBSD\n");
	break;
	case ELFOSABI_LINUX:
	printf("UNIX - Linux\n");
	break;
	case ELFOSABI_SOLARIS:
	printf("UNIX - Solaris\n");
	break;
	case ELFOSABI_IRIX:
	printf("UNIX - IRIX\n");
	break;
	case ELFOSABI_FREEBSD:
	printf("UNIX - FreeBSD\n");
	break;
	case ELFOSABI_TRU64:
	printf("UNIX - TRU64\n");
	break;
	case ELFOSABI_ARM:
	printf("ARM\n");
	break;
	case ELFOSABI_STANDALONE:
	printf("Standalone App\n");
	break;
	default:
	printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * print_abi_version - Prints the ABI version of an ELF header.
 * @e_ident: A pointer to an array containing the ELF ABI version.
 */
void print_abi_version(unsigned char *e_ident)
{
	printf(" ABI Version: %d\n",
	e_ident[EI_ABIVERSION]);
}

/**
 * print_file_type - Prints the type of an ELF header.
 * @e_type: The ELF type.
 * @e_ident: A pointer to an array containing the ELF class.
 */
void print_file_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
	e_type >>= 8;

	printf(" Type: ");

	switch (e_type)
	{
	case ET_NONE:
	printf("NONE (None)\n");
	break;
	case ET_REL:
	printf("REL (Relocatable file)\n");
	break;
	case ET_EXEC:
	printf("EXEC (Executable file)\n");
	break;
	case ET_DYN:
	printf("DYN (Shared object file)\n");
	break;
	case ET_CORE:
	printf("CORE (Core file)\n");
	break;
	default:
	printf("<unknown: %x>\n", e_type);
	}
}

/**
 * print_entry_point - Prints the entry point of an ELF header.
 * @e_entry: The address of the ELF entry point.
 * @e_ident: A pointer to an array containing the ELF class.
 */
void print_entry_point(unsigned long int e_entry, unsigned char *e_ident)
{
	printf(" Entry point address: ");

	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
	e_entry = ((e_entry << 8) & 0xFF00FF00) |
	((e_entry >> 8) & 0xFF00FF);
	e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
	printf("%#x\n", (unsigned int)e_entry);

	else
	printf("%#lx\n", e_entry);
}

/**
 * close_file - Closes a file.
 * @file_descriptor: The file descriptor of the file to be closed.
 *
 * Description: Exits with error code 98 if the file cannot be closed.
 */
void close_file(int file_descriptor)
{
	if (close(file_descriptor) == -1)
	{
	dprintf(STDERR_FILENO,
	"Error: Can't close file descriptor %d\n", file_descriptor);
	exit(98);
	}
}

/**
 * main - Displays the information contained in the ELF header at the start of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: Exits with error code 98 if the file is not an ELF File or the function fails.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr header;
	int file_descriptor;

	if (argc != 2)
	{
	dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
	exit(98);
	}

	file_descriptor = open(argv[1], O_RDONLY);
	if (file_descriptor == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
	exit(98);
	}

	if (read(file_descriptor, &header, sizeof(header)) != sizeof(header))
	{
	close_file(file_descriptor);
	dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
	exit(98);
	}

	check_elf(header.e_ident);
	printf("ELF Header:\n");
	print_magic_numbers(header.e_ident);
	print_class_info(header.e_ident);
	print_data_encoding(header.e_ident);
	print_version_info(header.e_ident);
	print_os_abi(header.e_ident);
	print_abi_version(header.e_ident);
	print_file_type(header.e_type, header.e_ident);
	print_entry_point(header.e_entry, header.e_ident);

	close_file(file_descriptor);
	return (0);
}
