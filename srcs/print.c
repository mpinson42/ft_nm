/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:38:54 by mpinson           #+#    #+#             */
/*   Updated: 2018/06/10 14:38:56 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			ft_secur_str(char *str, t_gen *g)
{
	int i;

	i = 0;
	if (str > g->end_ptr || str < g->ptr)
		return (-1);
	while (str[i])
	{
		if (&str[i] > g->end_ptr || &str[i] < g->ptr)
			return (-1);
		str++;
	}
	return (0);
}

char		ft_section(t_gen *g, long long int val)
{
	int i;

	(void)g;
	(void)val;
	i = 0;
	while (g->name_section[i])
		i++;
	if (i < g->sect)
		return ('?');
	if (ft_strncmp(g->name_section[g->sect - 1], "__text", 6) == 0)
		return ('t');
	else if (ft_strncmp(g->name_section[g->sect - 1], "__data", 6) == 0)
		return ('d');
	else if (ft_strncmp(g->name_section[g->sect - 1], "__bss", 5) == 0)
		return ('b');
	return ('s');
}

char		ft_char(t_gen *g, long long int val)
{
	int		t;
	char	c;

	t = N_TYPE & g->type;
	c = '?';
	if (N_STAB & g->type)
		c = '-';
	else if (t == N_UNDF)
		c = val ? 'c' : 'u';
	else if (t == N_ABS)
		c = 'a';
	else if (t == N_PBUD)
		c = 'u';
	else if (t == N_INDR)
		c = 'i';
	else if (t == N_WEAK_REF)
		c = 'W';
	else if (t == N_SECT)
		c = ft_section(g, val);
	if (N_EXT & g->type)
		c = ft_toupper(c);
	return (c);
}

void		printing(t_gen *g, char *nb, int i, char c)
{
	if (g->flag_o == 1)
	{
		ft_putstr(g->input);
		ft_putstr(": ");
	}
	if (g->is_32 && g->flag_u == 0)
	{
		while (c != 'U' && ft_strlen(nb) + ++i < 8)
			ft_putchar('0');
		c != 'U' ? ft_putstr(nb) : ft_putstr("        ");
	}
	else if (g->flag_u == 0)
	{
		while (c != 'U' && ft_strlen(nb) + ++i < 16)
			ft_putchar('0');
		c != 'U' ? ft_putstr(nb) : ft_putstr("                ");
	}
	if (g->flag_u == 0)
	{
		ft_putchar(' ');
		ft_putchar(c);
		ft_putchar(' ');
	}
}

void		print_nm(long long int add, int type, char *str, t_gen *g)
{
	char	*nb;
	char	c;
	int		i;

	(void)type;
	i = -1;
	c = ft_char(g, add);
	if (c == '-' || c == '?' || (g->flag_u == 1 && c != 'U'))
		return ;
	nb = unsigned_itoa_base(add, 16);
	printing(g, nb, i, c);
	ft_putstr(str);
	ft_putchar('\n');
	free(nb);
}
