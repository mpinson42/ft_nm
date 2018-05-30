#include "nm.h"

int nm(char *ptr, unsigned long long int size)
{
	unsigned int magic_number;
	t_gen g;

	g.ptr = ptr;
	g.end_ptr = ptr + size;
	magic_number = *(unsigned int *) ptr;
	g.is_32 = 0;
	if((unsigned int)magic_number == MH_MAGIC_64)
	{
		bin_64(&g);
	}
	else if((unsigned int)magic_number == MH_MAGIC)
	{
		g.is_32 = 1;
		bin_32(&g);
	}
	else if((unsigned int)magic_number == MH_CIGAM_64)
	{
		bin_64_revers(&g);
	}
	else if((unsigned int)magic_number == MH_CIGAM)
	{
		g.is_32 = 1;
		bin_32_revers(&g);
		//bin_64_revers(ptr);
	}

	else if((unsigned int)magic_number == FAT_MAGIC)
	{
		fat_32(&g);
	}
	else if((unsigned int)magic_number == FAT_MAGIC_64)
	{
		fat_64(&g);
	}
	else if((unsigned int)magic_number == FAT_CIGAM)
	{
		fat_32_revers(&g);
	}
	else if((unsigned int)magic_number == FAT_CIGAM_64)
	{
		fat_64_revers(&g);
	}
	return (0);
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
		if(nm(ptr, buf.st_size) == -1)
			return(-1);
		if(munmap(ptr, buf.st_size) < 0)
		{
			ft_putendl("error");
			return(-1);
		}
		i++;
	}

}
