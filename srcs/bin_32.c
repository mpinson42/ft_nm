#include "nm.h"

static char	**ft_test_error(char *str, struct nlist *array,
	int max, t_gen *g)
{
	int		i;
	char	**val1;

	i = -1;
	if (!(val1 = malloc(sizeof(char *) * max + 1)))
		return (NULL);
	while (++i < max)
	{
		if (ft_secur_str(str + array[i].n_un.n_strx, g) == -1)
			return (NULL);
		val1[i] = str + array[i].n_un.n_strx;
	}
	return (val1);
}

char		**sort_name_32(struct nlist *array,
	int max, char *str, t_gen *g)
{
	int		is_sort;
	int		i;
	char	**val1;
	int		y;

	if (!(val1 = ft_test_error(str, array, max, g)))
		return (NULL);
	is_sort = 1;
	while (is_sort)
	{
		i = -1;
		is_sort = 0;
		while (++i + 1 < max)
		{
			y = 0;
			while (val1[i][y] != 0 && val1[i][y] == val1[i + 1][y])
				y++;
			if (val1[i][y] > val1[i + 1][y])
			{
				is_sort = 1;
				ft_swap(&val1[i + 1], &val1[i]);
			}
		}
	}
	return (val1);
}

int			print_output_32(int nsyms, int sysmoff, int stroff, t_gen *g)
{
	int				y;
	char			*stringtable;
	struct nlist	*array;
	char			**str;

	if (g->ptr + sysmoff > g->end_ptr || g->ptr + stroff > g->end_ptr ||
		g->ptr + sysmoff < g->ptr || g->ptr + stroff < g->ptr)
		return (-1);
	array = (void *)g->ptr + sysmoff;
	stringtable = (void *)g->ptr + stroff;
	if (!(str = sort_name_32(array, nsyms, stringtable, g)))
		return (-1);
	g->i = -1;
	while (++g->i < nsyms)
	{
		y = -1;
		while (++y < nsyms)
		{
			g->type = array[y].n_type;
			g->sect = array[y].n_sect;
			g->desc = array[y].n_desc;
			g->is_32 = 1;
			if (ft_strcmp(str[g->i], stringtable + array[y].n_un.n_strx) == 0)
				print_nm(array[y].n_value, array[y].n_type,
					stringtable + array[y].n_un.n_strx, g);
		}
	}
	free(str);
	return (0);
}

int			bin_32(t_gen *g)
{
	uint32_t nsects;
	uint32_t i;
	struct section *section_32;
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


			section_32 = (void*)&g->sc_32[1];
			i += nsects;
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
		g->i++;
	}
	g->name_section = malloc(sizeof(char *) * (i + 1));

	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	g->i = 0;
	g->sc_32 = (struct segment_command *)g->lc;
	int test = 0;
	while (g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT)
		{
			g->sc_32 = (struct segment_command *)g->lc;
			nsects = g->sc_32->nsects;

			i = 0;
			section_32 = (struct section*)&g->sc_32[1];
			while(i < nsects)
			{
				g->name_section[test] = section_32[i].sectname;
				section_32 = (void*)section_32;
				i++;
				test++;
			}
			
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
		g->i++;
	}


	g->i = 0;
	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	while (g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SYMTAB)
		{
			g->sym = (struct symtab_command *)g->lc;
			if (print_output_32(g->sym->nsyms,
				g->sym->symoff, g->sym->stroff, g) == -1)
				return (-1);
			break ;
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
		g->i++;
	}
	return (0);
}
