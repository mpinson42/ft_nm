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

int			print_output(int nsyms, int sysmoff, int stroff, t_gen *g)
{
	char			*stringtable;
	struct nlist_64	*array;

	if (g->ptr + sysmoff > g->end_ptr || g->ptr + stroff > g->end_ptr ||
		g->ptr + sysmoff < g->ptr || g->ptr + stroff < g->ptr)
		return (-1);
	array = (void *)g->ptr + sysmoff;
	stringtable = (void *)g->ptr + stroff;
	if (g->flag_p == 0 && g->flag_r == 0)
	{
		if (!(g->str = sort_name(array, nsyms, stringtable, g)))
			return (-1);
	}
	else if (g->flag_r == 1)
		g->str = revers_sort(array, nsyms, stringtable, g);
	else
		g->str = deflault_sort(array, nsyms, stringtable, g);
	mamange_sort_nm_64(g, nsyms, array, stringtable);
	free(g->str);
	return (0);
}

int			count_segment_64(t_gen *g, struct section_64 **section,
	uint32_t nsects, uint32_t *i)
{
	g->header_64 = (struct mach_header_64 *)g->ptr;
	g->ncmds = g->header_64->ncmds;
	g->i = 0;
	if (g->ptr + sizeof(*g->header_64) > g->end_ptr ||
		g->ptr + sizeof(*g->header_64) < g->ptr)
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_64);
	g->i = -1;
	g->sc = (struct segment_command_64 *)g->lc;
	i[0] = 0;
	while (++g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT_64)
		{
			g->sc = (struct segment_command_64 *)g->lc;
			nsects = g->sc->nsects;
			section[0] = (void*)&g->sc[1];
			i[0] += nsects;
		}
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
	}
	return (0);
}

int			save_segment_64(t_gen *g, uint32_t nsects,
	struct section_64 *section)
{
	uint32_t	i;
	int			test;

	test = 0;
	while (++g->i < g->ncmds)
	{
		if (g->lc->cmd == LC_SEGMENT_64)
		{
			g->sc = (struct segment_command_64 *)g->lc;
			nsects = g->sc->nsects;
			i = -1;
			section = (struct section_64*)&g->sc[1];
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

int			search_befor_print(t_gen *g)
{
	g->lc = (void*)g->ptr + sizeof(*g->header_64);
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
			if (print_output(g->sym->nsyms,
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

int			bin_64(t_gen *g)
{
	uint32_t			i;
	struct section_64	*section;
	int					test;

	test = 0;
	if (count_segment_64(g, &section, 0, &i) == -1)
		return (-1);
	if (!(g->name_section = malloc(sizeof(char *) * (i + 1))))
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_64);
	g->i = -1;
	g->sc = (struct segment_command_64 *)g->lc;
	if (save_segment_64(g, 0, section) == -1)
		return (-1);
	search_befor_print(g);
	return (0);
}
