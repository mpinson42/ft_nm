/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:33:51 by mpinson           #+#    #+#             */
/*   Updated: 2018/05/30 14:35:04 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			print_output_32(int nsyms, int sysmoff, int stroff, t_gen *g)
{
	char			*stringtable;
	struct nlist	*array;

	if (g->ptr + sysmoff > g->end_ptr || g->ptr + stroff > g->end_ptr ||
		g->ptr + sysmoff < g->ptr || g->ptr + stroff < g->ptr)
		return (-1);
	array = (void *)g->ptr + sysmoff;
	stringtable = (void *)g->ptr + stroff;
	if (g->flag_p == 0 && g->flag_r == 0)
	{
		if (!(g->str = sort_name_32(array, nsyms, stringtable, g)))
			return (-1);
	}
	else if (g->flag_r == 1)
		g->str = revers_sort_32(array, nsyms, stringtable, g);
	else
		g->str = deflault_sort_32(array, nsyms, stringtable, g);
	mamange_sort_nm_32(g, nsyms, array, stringtable);
	free(g->str);
	return (0);
}

int			count_segment_32(t_gen *g, struct section **section,
	uint32_t nsects, uint32_t *i)
{
	g->header_32 = (struct mach_header *)g->ptr;
	g->ncmds = g->header_32->ncmds;
	g->i = 0;
	if (g->ptr + sizeof(*g->header_32) > g->end_ptr ||
		g->ptr + sizeof(*g->header_32) < g->ptr)
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	g->i = -1;
	g->sc_32 = (struct segment_command *)g->lc;
	i[0] = 0;
	while (++g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT)
		{
			g->sc_32 = (struct segment_command *)g->lc;
			nsects = g->sc_32->nsects;
			section[0] = (void*)&g->sc_32[1];
			i[0] += nsects;
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
	}
	return (0);
}

int			save_segment_32(t_gen *g, uint32_t nsects, struct section *section)
{
	uint32_t	i;
	int			test;

	test = 0;
	while (++g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT)
		{
			g->sc_32 = (struct segment_command *)g->lc;
			nsects = g->sc_32->nsects;
			i = -1;
			section = (struct section*)&g->sc_32[1];
			while (++i < nsects)
			{
				g->name_section[test] = section[i].sectname;
				section = (void*)section;
				test++;
			}
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
	}
	return (0);
}

int			search_befor_print_32(t_gen *g)
{
	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	g->i = -1;
	while (++g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SYMTAB)
		{
			g->sym = (struct symtab_command *)g->lc;
			if (g->nb_input != 1 && g->flag_o == 0)
			{
				ft_putstr("\n");
				ft_putstr(g->input);
				ft_putstr(":\n");
			}
			if (print_output_32(g->sym->nsyms,
				g->sym->symoff, g->sym->stroff, g) == -1)
				return (-1);
			break ;
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
	}
	return (0);
}

int			bin_32(t_gen *g)
{
	uint32_t			i;
	struct section		*section;
	int					test;

	test = 0;
	if (count_segment_32(g, &section, 0, &i) == -1)
		return (-1);
	if (!(g->name_section = malloc(sizeof(char *) * (i + 1))))
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	g->i = -1;
	g->sc_32 = (struct segment_command *)g->lc;
	if (save_segment_32(g, 0, section) == -1)
		return (-1);
	search_befor_print_32(g);
	return (0);
}
