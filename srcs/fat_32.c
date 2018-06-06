#include "nm.h"

static int verif(char *ptr_)
{
	static int prefer = 0;

	if(prefer < 5 && *(unsigned int *)ptr_ == MH_MAGIC_64)
	{
		prefer = 5;
		return(1);
	}
	else if(prefer < 2 && *(unsigned int *)ptr_ == MH_MAGIC)
	{
		prefer = 2;
		return(1);
	}
	else if(prefer < 4 && *(unsigned int *)ptr_ == MH_CIGAM_64)
	{
		prefer = 4;
		return(1);
	}
	else if(prefer < 1 && *(unsigned int *)ptr_ == MH_CIGAM)
	{
		prefer = 1;
		return(1);
	}
	return(-1);
}

int			fat_32_revers(t_gen *g)
{
	struct fat_header *fat_header;
	struct fat_arch *fat_arch;
	uint32_t ncmds;
	uint32_t i;
	int save = 0;

	fat_header = (struct fat_header*)g->ptr;
	ncmds = revers_uint32(fat_header->nfat_arch);
	if(g->ptr + sizeof(*fat_header) < g->ptr || g->ptr + sizeof(*fat_header) > g->end_ptr)
		return(0);
	fat_arch = (void*)g->ptr + sizeof(*fat_header);
	i = 0;	
	while (i < ncmds)
	{
			if(g->ptr + revers_uint32(fat_arch[i].offset) < g->ptr || g->ptr + revers_uint32(fat_arch[i].offset) > g->end_ptr)
				return(0);
			g->i = verif((void*)g->ptr + revers_uint32(fat_arch[i].offset));
			if(g->i != -1)
				save = i;
		//	nm((void*)g->ptr + revers_uint32(fat_arch[i].offset), revers_uint32(fat_arch[i].size));
		i++;
	}
	nm((void*)g->ptr + revers_uint32(fat_arch[save].offset), revers_uint32(fat_arch[save].size), g->input, g);
	return(0);
}

int			fat_64_revers(t_gen *g)
{
	struct fat_header *fat_header;
	struct fat_arch_64 *fat_arch;
	uint32_t ncmds;
	uint32_t i;
	int save = 0;

	fat_header = (struct fat_header*)g->ptr;
	ncmds = revers_uint32(fat_header->nfat_arch);
	if(g->ptr + sizeof(*fat_header) < g->ptr || g->ptr + sizeof(*fat_header) > g->end_ptr)
		return(0);
	fat_arch = (void*)g->ptr + sizeof(*fat_header);
	i = 0;	
	while (i < ncmds)
	{
		if(g->ptr + revers_uint32(fat_arch[i].offset) < g->ptr || g->ptr + revers_uint32(fat_arch[i].offset) > g->end_ptr)
				return(0);
			g->i = verif((void*)g->ptr + revers_uint32(fat_arch[i].offset));
			if(g->i != -1)
				save = i;
		//	nm((void*)g->ptr + revers_uint32(fat_arch[i].offset), revers_uint32(fat_arch[i].size));
		i++;
	}
	nm((void*)g->ptr + revers_uint32(fat_arch[save].offset), revers_uint32(fat_arch[save].size), g->input, g);
	return(0);
}

int			fat_64(t_gen *g)
{
	struct fat_header *fat_header;
	struct fat_arch_64 *fat_arch;
	uint32_t ncmds;
	uint32_t i;
	int save = 0;

	fat_header = (struct fat_header*)g->ptr;
	ncmds = revers_uint32(fat_header->nfat_arch);
	if(g->ptr + sizeof(*fat_header) < g->ptr || g->ptr + sizeof(*fat_header) > g->end_ptr)
		return(0);
	fat_arch = (void*)g->ptr + sizeof(*fat_header);
	i = 0;	
	while (i < ncmds)
	{
		if(g->ptr + revers_uint32(fat_arch[i].offset) < g->ptr || g->ptr + revers_uint32(fat_arch[i].offset) > g->end_ptr)
				return(0);
			g->i = verif((void*)g->ptr + fat_arch[i].offset);
			if(g->i != -1)
				save = i;
		//	nm((void*)g->ptr + revers_uint32(fat_arch[i].offset), revers_uint32(fat_arch[i].size));
		i++;
	}
	nm((void*)g->ptr + fat_arch[save].offset, fat_arch[save].size, g->input, g);
	return(0);
}

int			fat_32(t_gen *g)
{
	struct fat_header *fat_header;
	struct fat_arch *fat_arch;
	uint32_t ncmds;
	uint32_t i;
	int save = 0;

	fat_header = (struct fat_header*)g->ptr;
	ncmds = fat_header->nfat_arch;
	if(g->ptr + sizeof(*fat_header) < g->ptr || g->ptr + sizeof(*fat_header) > g->end_ptr)
		return(0);
	fat_arch = (void*)g->ptr + sizeof(*fat_header);
	i = 0;	
	while (i < ncmds)
	{
		if(g->ptr + revers_uint32(fat_arch[i].offset) < g->ptr || g->ptr + revers_uint32(fat_arch[i].offset) > g->end_ptr)
				return(0);
			g->i = verif((void*)g->ptr + fat_arch[i].offset);
			if(g->i != -1)
				save = i;
		//	nm((void*)g->ptr + revers_uint32(fat_arch[i].offset), revers_uint32(fat_arch[i].size));
		i++;
	}
	nm((void*)g->ptr + fat_arch[save].offset, fat_arch[save].size, g->input, g);
	return(0);
}
