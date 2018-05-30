#include "nm.h"

int ft_secur_str(char *str, t_gen *g)
{
	int i = 0;
	if(str > g->end_ptr || str < g->ptr)
		return (-1);
	while(str[i])
	{
		if(&str[i] > g->end_ptr || &str[i] < g->ptr)
			return (-1);
		str++;
	}
	return(0);
}


void ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

uint8_t revers_uint8(uint8_t n)
{
	return (n);
}

uint16_t revers_uint16(uint16_t n)
{
	return ((n >> 8) | (n << 8));
}

uint32_t revers_uint32(uint32_t n)
{

	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) | (n << 24));
}

uint64_t revers_uint64(uint64_t n)
{
	return ((n & 0xff00000000000000) >> 56 \
			| (n & 0x00ff000000000000) >> 40 \
			| (n & 0x0000ff0000000000) >> 24 \
			| (n & 0x000000ff00000000) >> 8 \
			| (n & 0x00000000ff000000) << 8 \
			| (n & 0x0000000000ff0000) << 24 \
			| (n & 0x000000000000ff00) << 40 \
			| (n & 0x00000000000000ff) << 56);
}

void print_nm(long long int add, int type, char *str, t_gen *g)
{
	char *nb = unsigned_itoa_base(add, 16);
	if(str[0] == 0)
		return;
	//printf("%s\n", unsigned_itoa_base(add, 16));
	int i = 0;
	if(g->is_32)
	{
		while(add != 0 && ft_strlen(nb) + i < 8)
		{
			ft_putchar('0');
			i++;
		}
		if(add != 0)
			ft_putstr(nb);
		else
			ft_putstr("        ");
	}
	else
	{
		while(add != 0 && ft_strlen(nb) + i < 16)
		{
			ft_putchar('0');
			i++;
		}
		if(add != 0)
			ft_putstr(nb);
		else
			ft_putstr("                ");
	}
	ft_putchar(' ');
	ft_putnbr(type);
	ft_putchar(' ');
	ft_putstr(str);
	//if(add != 0)
	//	ft_putnbr_lld(add);
	ft_putchar('\n');
	free(nb);
}