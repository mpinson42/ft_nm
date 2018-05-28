#include "nm.h"
	#include <stdio.h>

void print_output(int nsyms, int sysmoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct nlist_64 *array;

	array = (void *)ptr + sysmoff;
	stringtable = (void *)ptr + stroff;

	i = 0;
	while(i < nsyms)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void bin_64(char *ptr)
{
	int ncmds;
	int i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void*)ptr + sizeof(*header);
	while(i < ncmds)
	{
		if(lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}


}

void nm(char *ptr)
{
	int magic_number;

	magic_number = *(int *) ptr;
	if((unsigned int)magic_number == MH_MAGIC_64)
		bin_64(ptr);	
}

int main(int argc, char **argv)
{
	int 	fd;
	char	*ptr;
	struct stat buf;
	int i = 1;

	if(argc < 2)
	{
		ft_putendl("error");
		return(-1);
	}

	while(argv[i])
	{
		if((fd = open(argv[i], O_RDONLY)) < 0)
		{
			ft_putendl("error");
			return(-1);
		}
		if(fstat(fd, &buf) < 0)
		{
			ft_putendl("error");
			return(-1);
		}
		if((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			ft_putendl("error");
			return(-1);
		}
		nm(ptr);
		if(munmap(ptr, buf.st_size) < 0)
		{
			ft_putendl("error");
			return(-1);
		}
		i++;
	}

}
