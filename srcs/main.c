/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 10:36:09 by mpinson           #+#    #+#             */
/*   Updated: 2018/06/10 10:36:10 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		nm(char *ptr, unsigned long long int size, char *argv, t_gen *g)
{
	unsigned int magic_number;

	g->input = argv;
	g->ptr = ptr;
	g->end_ptr = ptr + size;
	magic_number = *(unsigned int *)ptr;
	g->is_32 = 0;
	if ((unsigned int)magic_number == MH_MAGIC_64)
		bin_64(g);
	else if ((unsigned int)magic_number == MH_MAGIC)
	{
		g->is_32 = 1;
		bin_32(g);
	}
	else if ((unsigned int)magic_number == FAT_MAGIC)
		fat_32(g);
	else if ((unsigned int)magic_number == FAT_MAGIC_64)
		fat_64(g);
	else if ((unsigned int)magic_number == FAT_CIGAM)
		fat_32_revers(g);
	else if ((unsigned int)magic_number == FAT_CIGAM_64)
		fat_64_revers(g);
	return (0);
}

int		ft_error(void)
{
	ft_putendl("error");
	return (-1);
}

int		ft_start_nm(t_gen *g, int argc, char **argv)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	while (g->count_flag < argc)
	{
		if ((fd = open(argv[g->count_flag], O_RDONLY)) < 0)
			return (ft_error());
		if (fstat(fd, &buf) < 0)
			return (ft_error());
		if ((ptr = mmap(0, buf.st_size, PROT_READ,
			MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (ft_error());
		if (nm(ptr, buf.st_size, argv[g->count_flag], g) == -1)
			return (-1);
		if (munmap(ptr, buf.st_size) < 0)
			return (ft_error());
		g->count_flag++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_gen g;

	if (argc < 2)
		return (ft_error());
	g.flag_p = 0;
	g.flag_o = 0;
	g.flag_r = 0;
	g.count_flag = 0;
	while (++g.count_flag < argc)
	{
		if (ft_strcmp("-p", argv[g.count_flag]) == 0)
			g.flag_p = 1;
		else if (ft_strcmp("-o", argv[g.count_flag]) == 0)
			g.flag_o = 1;
		else if (ft_strcmp("-r", argv[g.count_flag]) == 0)
			g.flag_r = 1;
		else if (ft_strcmp("-u", argv[g.count_flag]) == 0)
			g.flag_u = 1;
		else
			break ;
	}
	g.nb_input = argc - g.count_flag;
	ft_start_nm(&g, argc, argv);
}
