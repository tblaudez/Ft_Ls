/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:16:34 by tblaudez          #+#    #+#             */
/*   Updated: 2018/05/29 16:16:36 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_flags(char (*string)[STR_BUF],
	const char *restrict format, va_list ap, t_printf *list)
{
	int	k;

	list_init(list);
	k = 0;
	while (ft_charsrc("{#0-+ ", format[k]) >= 0)
		set_flags(list, format[k++]);
	if ((ft_isdigit(format[k]) && format[k] != '0'))
	{
		list->width = ft_atoi(format + k);
		k += ft_nbrdig(list->width, 10);
	}
	if (format[k] == '.' && (list->preci = ft_atoi(format + k + 1)) >= 0)
		k += ft_nbrdig(list->preci, 10) + (ft_isdigit(format[k + 1]) ? 1 : 0);
	if (ft_charsrc("hjzl", format[k]) >= 0)
		k += set_modifiers(list, format + k);
	list->let = format[k];
	if (ZERO && list->preci >= 0 &&
	ft_charsrc("DdiOouUixXpb", list->let) >= 0)
		FLAGS &= 0b101111;
	if (!format[k] && !((*string)[0] = '\0'))
		return (k);
	concat_string(string, list, ap);
	return (k + 1);
}

static void	apply_flags2(t_printf *list, char (*string)[STR_BUF],
	char (*cat)[CAT_BUF], char (*tmp)[256])
{
	int	size;

	size = ft_strlen(*cat);
	if (list->preci > size && ft_charsrc("dxXopui", list->let) >= 0)
	{
		ft_memset(*tmp + ft_strlen(*tmp), '0', list->preci - size);
		size += (list->preci - size);
	}
	else if (list->preci < size && list->preci >= 0 &&
	list->let == 's' && list->modif[0] != 'l')
	{
		(*cat)[list->preci] = '\0';
		size = list->preci;
	}
	if ((list->width -= size) > 0)
	{
		if (MINUS)
			ft_memset((*cat) + ft_strlen(*cat), ' ', list->width);
		else if (ZERO)
			ft_memset((*tmp) + ft_strlen(*tmp), '0', list->width);
		else
			ft_memset((*string) + ft_strlen(*string), ' ', list->width);
	}
	ft_strcat(*string, *tmp);
}

static void	apply_flags(t_printf *list, char (*string)[STR_BUF],
char (*cat)[CAT_BUF])
{
	char tmp[256];

	ft_bzero(tmp, 256);
	if (list->let == 'p' && ft_strcat(tmp, "0x"))
		list->width -= 2;
	if (HASH && ft_charsrc("xX", list->let) >= 0 && (*cat)[0] != '0' &&
	ft_strcat(ZERO ? *string : tmp, list->let == 'x' ? "0x" : "0X"))
		(list->width) -= 2;
	else if (HASH && list->let == 'o' && !(*cat)[CAT_BUF - 1] &&
	(*cat)[0] != '0' && ft_strcat(tmp, "0"))
	{
		(list->width)--;
		(list->preci)--;
	}
	if ((PLUS || SPACE) && ft_charsrc("id", list->let) >= 0 &&
	!(*cat)[CAT_BUF - 1] && ft_strcat(tmp, PLUS ? "+" : " "))
		(list->width)--;
	if (!list->preci && (*cat)[0] == '0' && list->let != 'p')
		if ((ft_charsrc("udixX", list->let) >= 0) ||
		(list->let == 'o' && !HASH))
			(*cat)[0] = '\0';
	if ((*cat)[CAT_BUF - 1] == '-' && ft_strcat(tmp, "-"))
		(list->width)--;
	apply_flags2(list, string, cat, &tmp);
}

void		concat_string(char (*string)[STR_BUF], t_printf *list, va_list ap)
{
	const char	conv[] = "cdsxXopui%b";
	int			i;
	char		cat[CAT_BUF];
	static void	(*func_tab[])(t_printf *list, va_list ap, char(*cat)[CAT_BUF]) =
	{&put_char, &put_dec, &put_str, &put_hex, &put_hex_cap,
	&put_oct, &put_mem, &put_unsigned, &put_dec, &put_char, &put_bin};

	ft_bzero(cat, CAT_BUF);
	i = -1;
	if ((ft_charsrc("DOUSC", list->let) >= 0))
	{
		ft_strcpy(list->modif, "l");
		list->let += 32;
	}
	if (ft_charsrc("cdsxXopui%b", list->let) < 0)
		cat[0] = list->let;
	else
		while (conv[++i])
			if (list->let == conv[i])
			{
				func_tab[i](list, ap, &cat);
				break ;
			}
	apply_flags(list, string, &cat);
	ft_strcat(*string, cat);
}

int			ft_printf(const char *restrict format, ...)
{
	char		string[STR_BUF];
	va_list		ap;
	t_printf	list;
	int			it[3];

	list_init(&list);
	va_start(ap, format);
	ft_bzero(string, STR_BUF);
	ft_setintarray(it, -1, 3);
	while (format[++(it[0])] && ++(it[1]) != STR_BUF)
	{
		if ((it[2] = ft_charsrc("{%", format[it[0]])) >= 0)
		{
			it[0] += !it[2] ? check_colors(&string, format + it[0]) :
			check_flags(&string, format + it[0] + 1, ap, &list);
			it[1] = ft_strlen(string) - 1;
		}
		else if (it[1] >= (STR_BUF * 0.75))
			write_buffer(&string, &list, &(it[1]), 1);
		else
			string[it[1]] = format[it[0]];
	}
	va_end(ap);
	return (write_buffer(&string, &list, &(it[1]), 0) < 0 ? -1 :
	it[1] + 1 + list.size);
}
