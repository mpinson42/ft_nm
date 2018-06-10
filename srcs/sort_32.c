/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:51:57 by mpinson           #+#    #+#             */
/*   Updated: 2018/06/10 14:52:01 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char		**ft_test_error(char *str, struct nlist *array,
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

char		**sort_name_32(struct nlist *array, int max, char *str, t_gen *g)
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

char		**revers_sort_32(struct nlist *array, int max, char *str, t_gen *g)
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
			if (val1[i][y] < val1[i + 1][y])
			{
				is_sort = 1;
				ft_swap(&val1[i + 1], &val1[i]);
			}
		}
	}
	return (val1);
}

char		**deflault_sort_32(struct nlist *array,
	int max, char *str, t_gen *g)
{
	char	**val1;

	if (!(val1 = ft_test_error(str, array, max, g)))
		return (NULL);
	return (val1);
}

int			mamange_sort_nm_32(t_gen *g, int nsyms,
	struct nlist	*array, char *stringtable)
{
	int y;

	g->i = -1;
	if (!(g->also_down = malloc(sizeof(char) * nsyms + 1)))
		return (-1);
	ft_bzero(g->also_down, nsyms + 1);
	while (++g->i < nsyms)
	{
		y = -1;
		while (++y < nsyms)
		{
			g->type = array[y].n_type;
			g->sect = array[y].n_sect;
			g->desc = array[y].n_desc;
			g->is_32 = 1;
			if (g->also_down[g->i] == 0 && ft_strcmp(g->str[g->i],
				stringtable + array[y].n_un.n_strx) == 0)
			{
				g->also_down[g->i] = 1;
				print_nm(array[y].n_value, array[y].n_type,
					stringtable + array[y].n_un.n_strx, g);
			}
		}
	}
	return (0);
}
