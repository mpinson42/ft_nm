#include "nm.h"

int			otools_32(t_gen *g)
{
	uint32_t nsects;
	uint32_t i;
	struct section *section;

	g->header_32 = (struct mach_header *)g->ptr;
	g->ncmds = g->header_32->ncmds;
	g->i = 0;
	if (g->ptr + sizeof(*g->header_32) > g->end_ptr ||
		g->ptr + sizeof(*g->header_32) < g->ptr)
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_32);


	g->i = 0;
	g->sc_32 = (struct segment_command *)g->lc;
	i = 0;
	while (g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT)
		{
			g->sc_32 = (struct segment_command *)g->lc;
			nsects = g->sc_32->nsects;
			i = 0;
			section = (struct section*)&g->sc_32[1];
			while(i < nsects)
			{
				if((char *)&section[i] < g->ptr || (char*)&section[i] > g->end_ptr)
					return(-1);
				if(ft_strncmp(section[i].sectname,"__text",6)==0 && ft_strncmp(section[i].segname,"__TEXT",6)==0)
				{
					char *add;
					uint32_t off = section[i].addr;
					uint8_t *c = (void*)g->ptr + section[i].offset;
					int add_0 = 0;

					uint32_t size = 1;
					char *str;
					ft_putstr(g->input);
					ft_putstr(":\nContents of (__TEXT,__text) section\n");
					add = unsigned_itoa_base(off, 16);
					while(add_0 + ft_strlen(add) < 8)
					{
						ft_putstr("0");
						add_0++;
					}
					ft_putstr(add);
					ft_putstr("\t");
					while(size <= section[i].size)
					{
						str = unsigned_itoa_base(c[size-1],16);
						if(ft_strlen(str) == 1)
							ft_putstr("0");
						ft_putstr(str);
						ft_putstr(" ");
						if(size % 16 == 0 )
						{
							off += 16;
							ft_putstr("\n");
							add = unsigned_itoa_base(off, 16);
							add_0 = 0;
							while(add_0 + ft_strlen(add) < 8)
							{
								ft_putstr("0");
								add_0++;
							}
							ft_putstr(add);
							ft_putstr("\t");
						}
						size++;
					}
				}
				i++;
			}
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
		g->i++;
	}
	ft_putstr("\n");
	return(0);
}