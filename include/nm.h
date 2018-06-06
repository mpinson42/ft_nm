#ifndef NM_H
# define NM_H

#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft.h"

#include <stdio.h>

typedef	struct		s_gen
{
	char	*ptr;
	int ncmds;
	int i;
	int y;
	char **str;
	char *stringtable;
	struct mach_header_64 *header_64;
	struct mach_header *header_32;
	struct load_command *lc;
	struct symtab_command *sym;
	struct fat_header	*fat_header_32;
	struct fat_arch *fa;
	int is_32;
	char 	*end_ptr;
	uint8_t type;
	uint8_t sect;
	int16_t desc;

	uint32_t nsects;

	struct segment_command_64 *sc;
	struct section_64 *section;

	struct segment_command *sc_32;
	struct section *section_32;

	char **name_section;

	char *input;
	int nb_input;

	char *also_down;

	int flag_d;
}					t_gen;

int ft_secur_str(char *str, t_gen *g);
int			bin_64_revers(t_gen *g);
void ft_swap(char **s1, char **s2);
int bin_64(t_gen *g);
int			bin_32(t_gen *g);
uint8_t revers_uint8(uint8_t num);
uint32_t revers_uint32(uint32_t num);
void print_nm(long long int add, int type, char *str, t_gen *g);
int			bin_32_revers(t_gen *g);
int			fat_32_revers(t_gen *g);
int nm(char *ptr, unsigned long long int size, char*argv, int argc);
uint64_t revers_uint64(uint64_t num);
uint16_t revers_uint16(uint16_t n);
int			fat_32(t_gen *g);
int			fat_64_revers(t_gen *g);
int			fat_64(t_gen *g);

int			otools_64(t_gen *g);
int			otools_32(t_gen *g);

int			otool_fat_32_revers(t_gen *g);
int			otool_fat_64_revers(t_gen *g);
int			otool_fat_64(t_gen *g);
int			otool_fat_32(t_gen *g);
int otool(char *ptr, unsigned long long int size, char*argv, int argc);

#endif