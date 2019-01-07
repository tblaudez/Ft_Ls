/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:19:44 by tblaudez          #+#    #+#             */
/*   Updated: 2018/08/06 16:43:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		putnbr_printf(intmax_t n, char (*cat)[CAT_BUF])
{
	if (n < 0)
	{
		(*cat)[CAT_BUF - 1] = '-';
		n *= -1;
	}
	itoabase_printf(n, 10, cat);
}

int			write_buffer(char (*string)[STR_BUF], t_printf *list, int *j, int x)
{
	int i;

	if (ERROR)
		return (-1);
	i = 0;
	while ((*string)[i])
	{
		if ((*string)[i] == -1)
			(*string)[i] = 0;
		i++;
	}
	write(1, string, (*j) + 1);
	if (x)
	{
		ft_bzero(string, STR_BUF);
		list->size += ((*j) + 1);
		*j = 0;
	}
	return (0);
}

void		put_bin(t_printf *list, va_list ap, char (*cat)[CAT_BUF])
{
	if (!((list->modif)[0]))
		itoabase_printf(va_arg(ap, unsigned int), 2, cat);
	else if (!ft_strcmp(list->modif, "h"))
		itoabase_printf((unsigned short)va_arg(ap, int), 2, cat);
	else if (!ft_strcmp(list->modif, "l"))
		itoabase_printf(va_arg(ap, unsigned long), 2, cat);
	else if (!ft_strcmp(list->modif, "hh"))
		itoabase_printf((unsigned char)va_arg(ap, int), 2, cat);
	else if (!ft_strcmp(list->modif, "ll"))
		itoabase_printf(va_arg(ap, unsigned long long), 2, cat);
	else if (!ft_strcmp(list->modif, "j"))
		itoabase_printf(va_arg(ap, uintmax_t), 2, cat);
	else if (!ft_strcmp(list->modif, "z"))
		itoabase_printf(va_arg(ap, size_t), 2, cat);
}

int			check_colors(char (*string)[STR_BUF], const char *restrict format)
{
	int			j;
	char		clr[12];
	const char	*colors[] = {"red", "green", "yellow",
	"blue", "magenta", "cyan", "bold", "dim", "underlined",
	"blink", "reverse", "hidden", "eoc"};
	const char	*code[] = {RED, GREEN, YELLOW, BLUE,
	MAGENTA, CYAN, BOLD, DIM, UNDERLINED, BLINK, REVERSE,
	HIDDEN, RESET};

	j = -1;
	ft_bzero(clr, 10);
	ft_strncpy(clr, format + 1, ft_charsrc((char*)format, '}') - 1);
	while (++j < 13)
		if (!(ft_strcmp((char *)clr, colors[j])))
		{
			ft_strcat(*string, code[j]);
			break ;
		}
	if (j >= 13)
		(*string)[ft_strlen(*string)] = '{';
	return (j < 13 ? ft_strlen(clr) + 1 : 0);
}
