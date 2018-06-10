/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otools_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 11:57:32 by mpinson           #+#    #+#             */
/*   Updated: 2018/06/10 11:57:34 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	otools_32_printing2(t_algo *a)
{
	while (a->size <= a->section[a->i].size)
	{
		a->str = unsigned_itoa_base(a->c[a->size - 1], 16);
		if (ft_strlen(a->str) == 1)
			ft_putstr("0");
		ft_putstr(a->str);
		ft_putstr(" ");
		if (a->size % 16 == 0)
		{
			a->off += 16;
			ft_putstr("\n");
			a->add = unsigned_itoa_base(a->off, 16);
			a->add_0 = 0;
			while (a->add_0 + ft_strlen(a->add) < 8)
			{
				ft_putstr("0");
				a->add_0++;
			}
			ft_putstr(a->add);
			ft_putstr("\t");
			free(a->add);
		}
		free(a->str);
		a->size++;
	}
}

void	otools_32_printing1(t_algo *a, t_gen *g)
{
	a->off = a->section[a->i].addr;
	a->c = (void*)g->ptr + a->section[a->i].offset;
	a->add_0 = 0;
	a->size = 1;
	ft_putstr(g->input);
	ft_putstr(":\nContents of (__DATA,__data) section\n");
	a->add = unsigned_itoa_base(a->off, 16);
	while (a->add_0 + ft_strlen(a->add) < 8)
	{
		ft_putstr("0");
		a->add_0++;
	}
	ft_putstr(a->add);
	ft_putstr("\t");
	free(a->add);
}

int		otools_32_trouver(t_algo *a, t_gen *g)
{
	a->nsects = g->sc_32->nsects;
	a->i = 0;
	a->section = (struct section*)&g->sc_32[1];
	while (a->i < a->nsects)
	{
		if ((char *)&a->section[a->i] < g->ptr ||
			(char*)&a->section[a->i] > g->end_ptr)
			return (-1);
		if (g->flag_d == 0 && ft_strncmp(a->section[a->i].sectname,
			"__text", 6) == 0 && ft_strncmp(
			a->section[a->i].segname, "__TEXT", 6) == 0)
		{
			otools_32_printing1(a, g);
			otools_32_printing2(a);
		}
		else if (g->flag_d == 1 && ft_strncmp(a->section[a->i].sectname,
			"__data", 6) == 0 && ft_strncmp(a->section[a->i].segname,
			"__DATA", 6) == 0)
		{
			otools_32_printing1(a, g);
			otools_32_printing2(a);
		}
		a->i++;
	}
	return (0);
}

int		otools_32(t_gen *g)
{
	t_algo a;

	g->header_32 = (struct mach_header *)g->ptr;
	g->ncmds = g->header_32->ncmds;
	g->i = 0;
	if (g->ptr + sizeof(*g->header_32) > g->end_ptr ||
		g->ptr + sizeof(*g->header_32) < g->ptr)
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	g->i = 0;
	g->sc_32 = (struct segment_command *)g->lc;
	a.i = 0;
	while (g->i < g->ncmds)
	{
		g->sc_32 = (struct segment_command *)g->lc;
		if (g->lc->cmd == LC_SEGMENT && otools_32_trouver(&a, g) == -1)
			return (-1);
		if ((char*)g->lc + g->lc->cmdsize > g->end_ptr ||
			(char*)g->lc + g->lc->cmdsize < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + g->lc->cmdsize;
		g->i++;
	}
	ft_putstr("\n");
	return (0);
}
