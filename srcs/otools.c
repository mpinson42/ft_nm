#include "nm.h"

int otool(char *ptr, unsigned long long int size, char*argv, t_gen *g)
{
	unsigned int magic_number;

	g->input = argv;
	g->ptr = ptr;
	g->end_ptr = ptr + size;
	magic_number = *(unsigned int *) ptr;
	g->is_32 = 0;
	if((unsigned int)magic_number == MH_MAGIC_64)
	{
		otools_64(g);
	}
	else if((unsigned int)magic_number == MH_MAGIC)
	{
		g->is_32 = 1;
		otools_32(g);
	}
/*	else if((unsigned int)magic_number == MH_CIGAM_64)
	{
		bin_64_revers(&g);
	}
	else if((unsigned int)magic_number == MH_CIGAM)
	{
		g.is_32 = 1;
		bin_32_revers(&g);
		//bin_64_revers(ptr);
	}*/

	else if((unsigned int)magic_number == FAT_MAGIC)
	{
		otool_fat_32(g);
	}
	else if((unsigned int)magic_number == FAT_MAGIC_64)
	{
		otool_fat_64(g);
	}
	else if((unsigned int)magic_number == FAT_CIGAM)
	{
		otool_fat_32_revers(g);
	}
	else if((unsigned int)magic_number == FAT_CIGAM_64)
	{
		otool_fat_64_revers(g);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int 	fd;
	char	*ptr;
	struct stat buf;
	int i = 1;
	t_gen g;

	if(argc < 2)
	{
		ft_putendl("error");
		return(-1);
	}

	g.flag_d = 0;
	while(i < argc)
	{
		if(ft_strcmp("-d", argv[i]) == 0)
		{
			g.flag_d = 1;
		}
		else
			break;
		i++;
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
		g.nb_input = argc; 
		if(otool(ptr, buf.st_size, argv[i], &g) == -1)
			return(-1);
		if(munmap(ptr, buf.st_size) < 0)
		{
			ft_putendl("error");
			return(-1);
		}
		i++;
	}

}
