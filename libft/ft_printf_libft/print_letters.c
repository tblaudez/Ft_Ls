/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_letters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:10:01 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/04 14:07:12 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			put_unicode(char (*cat)[CAT_BUF], wchar_t uchar, t_printf *list)
{
	int i;

	list->let = list->let;
	i = ft_strlen(*cat);
	if (uchar < 128)
		(*cat)[i] = uchar;
	else if (uchar < 2048)
	{
		(*cat)[i] = 0b11000000 | ((uchar >> 6) & 0b00011111);
		(*cat)[++i] = 0b10000000 | (uchar & 0b00111111);
	}
	else if (uchar < 65536)
	{
		(*cat)[i] = 0b11100000 | ((uchar >> 12) & 0b00001111);
		(*cat)[++i] = 0b10000000 | ((uchar >> 6) & 0b00111111);
		(*cat)[++i] = 0b10000000 | (uchar & 0b00111111);
	}
	else
	{
		(*cat)[i] = 0b11110000 | ((uchar >> 18) & 0b00000111);
		(*cat)[++i] = 0b10000000 | ((uchar >> 12) & 0b00111111);
		(*cat)[++i] = 0b10000000 | ((uchar >> 6) & 0b00111111);
		(*cat)[++i] = 0b10000000 | (uchar & 0b00111111);
	}
	return ((*cat)[0] ? 1 : 0);
}

void		put_str(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	void	*str;
	wchar_t *str2;
	int		i;

	i = 1;
	if (!((list->modif)[0]))
	{
		str = va_arg(ap, char*);
		str || !(list->preci) ? ft_strncat((*cat), str, CAT_BUF - 1) :
		ft_strcat((*cat), "(null)");
		if (str && ft_strlen(str) >= CAT_BUF && (FLAGS |= 1))
			write(2, "Error : string argument too wide for %s\n", 41);
	}
	else if (!ft_strcmp(list->modif, "l"))
	{
		str2 = va_arg(ap, wchar_t*);
		if (str2)
			while (*str2 && i)
				i = put_unicode(cat, *(str2++), list);
		else
			ft_strcat((*cat), "(null)");
	}
}

void		put_mem(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	char	tmp[CAT_BUF];

	ft_bzero(tmp, CAT_BUF);
	itoabase_printf(va_arg(ap, size_t), 16, &tmp);
	if (!(!list->preci && tmp[0] == '0'))
		ft_strcat(*cat, tmp);
}

void		put_char(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	if (list->let == '%')
		(*cat)[0] = '%';
	else if (!((list->modif)[0]))
		(*cat)[0] = (char)va_arg(ap, int);
	else if (!ft_strcmp(list->modif, "l"))
		put_unicode(cat, va_arg(ap, wint_t), list);
	if (!(*cat)[0])
		(*cat)[0] = -1;
}
