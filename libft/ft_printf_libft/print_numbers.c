/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:13:47 by tblaudez          #+#    #+#             */
/*   Updated: 2018/05/31 12:24:13 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_dec(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	if (!((list->modif)[0]))
		putnbr_printf(va_arg(ap, int), cat);
	else if (!ft_strcmp(list->modif, "h"))
		putnbr_printf((short)va_arg(ap, int), cat);
	else if (!ft_strcmp(list->modif, "l"))
		putnbr_printf(va_arg(ap, long), cat);
	else if (!ft_strcmp(list->modif, "hh"))
		putnbr_printf((signed char)va_arg(ap, int), cat);
	else if (!ft_strcmp(list->modif, "ll"))
		putnbr_printf(va_arg(ap, long long), cat);
	else if (!ft_strcmp(list->modif, "j"))
		putnbr_printf(va_arg(ap, intmax_t), cat);
	else if (!ft_strcmp(list->modif, "z"))
		putnbr_printf(va_arg(ap, ssize_t), cat);
}

void	put_hex(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	if (!((list->modif)[0]))
		itoabase_printf(va_arg(ap, unsigned int), 16, cat);
	else if (!ft_strcmp(list->modif, "h"))
		itoabase_printf((unsigned short)va_arg(ap, int), 16, cat);
	else if (!ft_strcmp(list->modif, "l"))
		itoabase_printf(va_arg(ap, unsigned long), 16, cat);
	else if (!ft_strcmp(list->modif, "hh"))
		itoabase_printf((unsigned char)va_arg(ap, int), 16, cat);
	else if (!ft_strcmp(list->modif, "ll"))
		itoabase_printf(va_arg(ap, unsigned long long), 16, cat);
	else if (!ft_strcmp(list->modif, "j"))
		itoabase_printf(va_arg(ap, uintmax_t), 16, cat);
	else if (!ft_strcmp(list->modif, "z"))
		itoabase_printf(va_arg(ap, size_t), 16, cat);
}

void	put_hex_cap(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	int	i;

	put_hex(list, ap, cat);
	i = 0;
	while ((*cat)[i])
	{
		(*cat)[i] -= 32;
		i++;
	}
}

void	put_oct(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	if (!((list->modif)[0]))
		itoabase_printf(va_arg(ap, unsigned int), 8, cat);
	else if (!ft_strcmp(list->modif, "h"))
		itoabase_printf((unsigned short)va_arg(ap, int), 8, cat);
	else if (!ft_strcmp(list->modif, "l"))
		itoabase_printf(va_arg(ap, unsigned long), 8, cat);
	else if (!ft_strcmp(list->modif, "hh"))
		itoabase_printf((unsigned char)va_arg(ap, int), 8, cat);
	else if (!ft_strcmp(list->modif, "ll"))
		itoabase_printf(va_arg(ap, unsigned long long), 8, cat);
	else if (!ft_strcmp(list->modif, "j"))
		itoabase_printf(va_arg(ap, uintmax_t), 8, cat);
	else if (!ft_strcmp(list->modif, "z"))
		itoabase_printf(va_arg(ap, size_t), 8, cat);
}

void	put_unsigned(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	if (!((list->modif)[0]))
		itoabase_printf(va_arg(ap, unsigned int), 10, cat);
	else if (!ft_strcmp(list->modif, "h"))
		itoabase_printf((unsigned short)va_arg(ap, int), 10, cat);
	else if (!ft_strcmp(list->modif, "l"))
		itoabase_printf(va_arg(ap, unsigned long), 10, cat);
	else if (!ft_strcmp(list->modif, "hh"))
		itoabase_printf((unsigned char)va_arg(ap, int), 10, cat);
	else if (!ft_strcmp(list->modif, "ll"))
		itoabase_printf(va_arg(ap, unsigned long long), 10, cat);
	else if (!ft_strcmp(list->modif, "j"))
		itoabase_printf(va_arg(ap, uintmax_t), 10, cat);
	else if (!ft_strcmp(list->modif, "z"))
		itoabase_printf(va_arg(ap, size_t), 10, cat);
}
