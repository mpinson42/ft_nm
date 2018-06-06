#include "nm.h"

int nm(char *ptr, unsigned long long int size, char*argv, t_gen *g)
{
	unsigned int magic_number;

	g->input = argv;
	g->ptr = ptr;
	g->end_ptr = ptr + size;
	magic_number = *(unsigned int *) ptr;
	g->is_32 = 0;
	if((unsigned int)magic_number == MH_MAGIC_64)
	{
		bin_64(g);
	}
	else if((unsigned int)magic_number == MH_MAGIC)
	{
		g->is_32 = 1;
		bin_32(g);
	}
/*	else if((unsigned int)magic_number == MH_CIGAM_64)
	{
		printf("test\n");
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
		fat_32(g);
	}
	else if((unsigned int)magic_number == FAT_MAGIC_64)
	{
		fat_64(g);
	}
	else if((unsigned int)magic_number == FAT_CIGAM)
	{
		fat_32_revers(g);
	}
	else if((unsigned int)magic_number == FAT_CIGAM_64)
	{
		fat_64_revers(g);
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

	g.flag_p = 0;
	g.flag_o = 0;
	g.flag_r = 0;
	g.count_flag = 0;
	while(i < argc)
	{
		if(ft_strcmp("-p", argv[i]) == 0)
		{
			g.flag_p = 1;
		}
		else if(ft_strcmp("-o", argv[i]) == 0)
		{
			g.flag_o = 1;
		}
		else if(ft_strcmp("-r", argv[i]) == 0)
		{
			g.flag_r = 1;
		}
		else
			break;
		g.count_flag++;
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
		if(nm(ptr, buf.st_size, argv[i], &g) == -1)
			return(-1);
		if(munmap(ptr, buf.st_size) < 0)
		{
			ft_putendl("error");
			return(-1);
		}
		i++;
	}

}
