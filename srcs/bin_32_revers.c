/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32_revers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:47:23 by mpinson           #+#    #+#             */
/*   Updated: 2018/05/30 14:47:25 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char		**sort_name_32_revers(struct nlist *array,
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

int			print_output_32_revers(int nsyms, int sysmoff, int stroff, t_gen *g)
{
	char			*stringtable;
	struct nlist	*array;
	char			**str;

	if (g->ptr + sysmoff > g->end_ptr || g->ptr + stroff > g->end_ptr ||
		g->ptr + sysmoff < g->ptr || g->ptr + stroff < g->ptr)
		return (-1);
	array = (void *)g->ptr + sysmoff;
	stringtable = (void *)g->ptr + stroff;
	if (!(str = sort_name_32_revers(array, nsyms, stringtable, g)))
		return (-1);
	g->i = -1;
	while (++g->i < nsyms)
	{
		g->y = -1;
		while (++g->y < nsyms)
		{
			g->type = revers_uint8(array[g->y].n_type);
			g->sect = revers_uint8(array[g->y].n_sect);
			g->desc = revers_uint16(array[g->y].n_desc);
			g->is_32 = 1;
			if (ft_strcmp(str[g->i], stringtable + array[g->y].n_un.n_strx) == 0)
				print_nm(revers_uint32(array[g->y].n_value),
					revers_uint8(array[g->y].n_type),
					stringtable + array[g->y].n_un.n_strx, 0);
		}
	}
	free(str);
	return (0);
}

int			bin_32_revers(t_gen *g)
{
	g->header_32 = (struct mach_header *)g->ptr;
	g->ncmds = revers_uint32(g->header_32->ncmds);
	g->i = 0;
	if (g->ptr + sizeof(*g->header_32) > g->end_ptr ||
		g->ptr + sizeof(*g->header_32) < g->ptr)
		return (-1);
	g->lc = (void*)g->ptr + sizeof(*g->header_32);
	while (g->i < g->ncmds)
	{
		if (revers_uint32(g->lc->cmd) == LC_SYMTAB)
		{
			g->sym = (struct symtab_command *)g->lc;
			if (print_output_32_revers(revers_uint32(g->sym->nsyms),
				revers_uint32(g->sym->symoff), revers_uint32(g->sym->stroff), g) == -1)
				return (-1);
			break ;
		}
		if ((char*)g->lc + revers_uint32(g->lc->cmdsize) > g->end_ptr ||
			(char*)g->lc + revers_uint32(g->lc->cmdsize) < g->ptr)
			return (-1);
		g->lc = (void *)g->lc + revers_uint32(g->lc->cmdsize);
		g->i++;
	}
	return (0);
}
