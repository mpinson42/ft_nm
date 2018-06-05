#include "nm.h"

int			otools_64(t_gen *g)
{
	uint32_t nsects;
	uint32_t i;
	struct section_64 *section;

	g->header_64 = (struct mach_header_64 *)g->ptr;
	g->ncmds = g->header_64->ncmds;
	g->i = 0;
	if (g->ptr + sizeof(*g->header_64) > g->end_ptr ||
		g->ptr + sizeof(*g->header_64) < g->ptr)
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_64);


	g->i = 0;
	g->sc = (struct segment_command_64 *)g->lc;
	i = 0;
	while (g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT_64)
		{
			g->sc = (struct segment_command_64 *)g->lc;
			nsects = g->sc->nsects;

			i = 0;
			section = (struct section_64*)&g->sc[1];
			while(i < nsects)
			{
				if(ft_strncmp(section[i].sectname,"__text",6)==0 && ft_strncmp(section[i].segname,"__TEXT",6)==0)
				{
					char *str = unsigned_itoa_base(section[i].addr,16);
					uint8_t *c = (void*)g->ptr + section[i].offset;

					int size = 0;
					while(size < section[i].size)
					{
						str = unsigned_itoa_base(c[size],16);
						if(ft_strlen(str) == 1)
							ft_putstr("0");
						ft_putstr(str);
						ft_putstr(" ");
						if(size % 16 == 0 && size != 0)
							ft_putstr("\n");
						size++;
					}
					//printf("%s\n", str);
					section = (void*)section;
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
	return(0);
}