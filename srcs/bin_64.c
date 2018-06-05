/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:33:51 by mpinson           #+#    #+#             */
/*   Updated: 2018/05/30 14:35:04 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char	**ft_test_error(char *str, struct nlist_64 *array,
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

char		**sort_name(struct nlist_64 *array,
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

int			print_output(int nsyms, int sysmoff, int stroff, t_gen *g)
{
	int				y;
	char			*stringtable;
	struct nlist_64	*array;
	char			**str;

	if (g->ptr + sysmoff > g->end_ptr || g->ptr + stroff > g->end_ptr ||
		g->ptr + sysmoff < g->ptr || g->ptr + stroff < g->ptr)
		return (-1);
	array = (void *)g->ptr + sysmoff;
	stringtable = (void *)g->ptr + stroff;
	if (!(str = sort_name(array, nsyms, stringtable, g)))
		return (-1);
	g->i = -1;
	g->also_down = malloc(sizeof(char) * nsyms + 1);
	ft_bzero(g->also_down, nsyms + 1);
	while (++g->i < nsyms)
	{
		y = -1;
		while (++y < nsyms)
		{
			g->type = array[y].n_type;
			g->sect = array[y].n_sect;
			g->desc = array[y].n_desc;
			g->is_32 = 0;
			if (g->also_down[g->i] == 0 && ft_strcmp(str[g->i], stringtable + array[y].n_un.n_strx) == 0)
			{
				g->also_down[g->i] = 1;
				print_nm(array[y].n_value, array[y].n_type,
					stringtable + array[y].n_un.n_strx, g);
			}
		}

	}
	free(str);
	return (0);
}

int			bin_64(t_gen *g)
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


			section = (void*)&g->sc[1];
			i += nsects;
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
		g->i++;
	}
	g->name_section = malloc(sizeof(char *) * (i + 1));

	g->lc = (void*)g->ptr + sizeof(*g->header_64);
	g->i = 0;
	g->sc = (struct segment_command_64 *)g->lc;
	int test = 0;
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
				g->name_section[test] = section[i].sectname;
				section = (void*)section;
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


	
	//exit(0);







	g->lc = (void*)g->ptr + sizeof(*g->header_64);
	g->i = 0;
	while (g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SYMTAB)
		{
			g->sym = (struct symtab_command *)g->lc;
			if(g->nb_input != 2)
			{
				ft_putstr("\n");
				ft_putstr(g->input);
				ft_putstr(":\n");
			}
			if (print_output(g->sym->nsyms,
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
