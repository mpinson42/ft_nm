/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:58:13 by mpinson           #+#    #+#             */
/*   Updated: 2017/04/06 15:16:59 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_len(uintmax_t n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static char	*init(int *i)
{
	char *cmp;

	cmp = "0123456789abcdef";
	i[0] = 0;
	return (cmp);
}

static char	*free_str(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_strsub(str, 1, ft_strlen(str) - 1);
	free(tmp);
	return (str);
}

char		*unsigned_itoa_base(uintmax_t n, int base)
{
	int		i;
	int		len;
	char	*str;
	char	*cmp;

	cmp = init(&i);
	len = ft_get_len(n, base);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len + 1] = 0;
	while (len + 1)
	{
		str[len] = cmp[n % base];
		n = n / base;
		len--;
	}
	if (str[0] == '0')
		str = free_str(str);
	return (str);
}
