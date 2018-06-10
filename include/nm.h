/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:53:33 by mpinson           #+#    #+#             */
/*   Updated: 2018/06/10 14:53:36 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft.h"

typedef	struct					s_gen
{
	char						*ptr;
	int							ncmds;
	int							i;
	int							y;
	char						**str;
	char						*stringtable;
	struct mach_header_64		*header_64;
	struct mach_header			*header_32;
	struct load_command			*lc;
	struct symtab_command		*sym;
	struct fat_header			*fat_header_32;
	struct fat_arch				*fa;
	int							is_32;
	char						*end_ptr;
	uint8_t						type;
	uint8_t						sect;
	int16_t						desc;
	uint32_t					nsects;
	struct segment_command_64	*sc;
	struct section_64			*section;
	struct segment_command		*sc_32;
	struct section				*section_32;
	char						**name_section;
	char						*input;
	int							nb_input;
	char						*also_down;
	int							flag_d;
	int							flag_p;
	int							flag_o;
	int							flag_r;
	int							flag_u;
	int							count_flag;
}								t_gen;

typedef	struct					s_algo
{
	uint32_t					nsects;
	uint32_t					i;
	struct section				*section;
	struct section_64			*section_64;
	char						*add;
	uint32_t					off;
	uint64_t					off_64;
	uint8_t						*c;
	char						*str;
	int							add_0;
	uint32_t					size;
	char						**tab;
}								t_algo;

int								ft_secur_str(char *str, t_gen *g);
int								bin_64_revers(t_gen *g);
void							ft_swap(char **s1, char **s2);
int								bin_64(t_gen *g);
int								bin_32(t_gen *g);
uint8_t							revers_uint8(uint8_t num);
uint32_t						revers_uint32(uint32_t num);
void							print_nm(long long int add,
	int type, char *str, t_gen *g);
int								bin_32_revers(t_gen *g);
int								fat_32_revers(t_gen *g);
int								nm(char *ptr,
	unsigned long long int size, char*argv, t_gen *g);
uint64_t						revers_uint64(uint64_t num);
uint16_t						revers_uint16(uint16_t n);
int								fat_32(t_gen *g);
int								fat_64_revers(t_gen *g);
int								fat_64(t_gen *g);
char							**ft_test_error_64(char *str,
	struct nlist_64 *array, int max, t_gen *g);
int								otools_64(t_gen *g);
int								otools_32(t_gen *g);
int								otool_fat_32_revers(t_gen *g);
int								otool_fat_64_revers(t_gen *g);
int								otool_fat_64(t_gen *g);
int								otool_fat_32(t_gen *g);
int								otool(char *ptr,
	unsigned long long int size, char*argv, t_gen *g);
int								ft_error(void);
char							**sort_name(struct nlist_64 *array,
	int max, char *str, t_gen *g);
char							**revers_sort(struct nlist_64 *array,
	int max, char *str, t_gen *g);
char							**deflault_sort(struct nlist_64 *array,
	int max, char *str, t_gen *g);
int								mamange_sort_nm_64(t_gen *g,
	int nsyms, struct nlist_64	*array, char *stringtable);
char							**sort_name_32(struct nlist *array,
	int max, char *str, t_gen *g);
char							**revers_sort_32(struct nlist *array,
	int max, char *str, t_gen *g);
char							**deflault_sort_32(struct nlist *array,
	int max, char *str, t_gen *g);
int								mamange_sort_nm_32(t_gen *g,
	int nsyms, struct nlist	*array, char *stringtable);

#endif
