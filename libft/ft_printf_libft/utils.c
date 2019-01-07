/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 11:04:38 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/08 16:18:57 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		itoabase_printf(uintmax_t nbr, short base, char (*cat)[CAT_BUF])
{
	short		i;
	uintmax_t	tmp;

	i = 1;
	tmp = nbr;
	while ((tmp /= base) > 0)
		i++;
	(*cat)[i] = '\0';
	while (i--)
	{
		(*cat)[i] = (nbr % base) + (nbr % base > 9 ? 'a' - 10 : '0');
		nbr /= base;
	}
}

int			set_modifiers(t_printf *list, const char *restrict format)
{
	int			i;

	(list->modif)[0] = *format;
	if (*(format + 1) == *format)
		(list->modif)[1] = *(format + 1);
	i = 1;
	while (ft_charsrc("hjzl", *(format + i)) >= 0)
		i++;
	return (i);
}

void		set_flags(t_printf *list, char c)
{
	if (c == '#')
		FLAGS |= (1 << 5);
	else if (c == '0')
		FLAGS |= (1 << 4);
	else if (c == '-')
		FLAGS |= (1 << 3);
	else if (c == '+')
		FLAGS |= (1 << 2);
	else if (c == ' ')
		FLAGS |= (1 << 1);
	if (MINUS && ZERO)
		FLAGS &= 0b101111;
	if (PLUS && SPACE)
		FLAGS &= 0b000100;
}

void		list_init(t_printf *list)
{
	list->flags = 0;
	list->width = -1;
	list->preci = -1;
	ft_bzero(list->modif, 3);
	list->let = '\0';
	list->size = 0;
}
