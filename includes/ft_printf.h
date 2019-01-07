/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:16:58 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/08 15:50:47 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# include <limits.h>
# include "libft.h"

# define STR_BUF 4096
# define CAT_BUF 2048

# define FLAGS list->flags
# define HASH (list->flags & (1 << 5))
# define ZERO (list->flags & (1 << 4))
# define MINUS (list->flags & (1 << 3))
# define PLUS (list->flags & (1 << 2))
# define SPACE (list->flags & (1 << 1))
# define ERROR (list->flags & 1)

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define BOLD "\x1b[1m"
# define DIM "\x1b[2m"
# define UNDERLINED "\x1b[4m"
# define BLINK "\x1b[5m"
# define REVERSE "\x1b[7m"
# define HIDDEN "\x1b[8m"
# define RESET "\x1b[0m"

typedef struct	s_printf
{
	char		flags;
	int			width;
	int			preci;
	char		modif[3];
	char		let;
	int			size;
}				t_printf;

int				ft_printf(const char *restrict format, ...);
void			put_dec(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_hex(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_hex_cap(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_oct(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_unsigned(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_char(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_str(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_mem(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			put_bin(t_printf *list, va_list ap, char (*cat)[CAT_BUF]);
void			itoabase_printf(uintmax_t nbr, short base,
				char (*cat)[CAT_BUF]);
void			putnbr_printf(intmax_t n, char (*cat)[CAT_BUF]);
int				check_flags(char (*string)[STR_BUF],
				const char *restrict format, va_list ap, t_printf *list);
void			concat_string(char (*string)[STR_BUF], t_printf *list,
				va_list ap);
void			list_init(t_printf *list);
void			set_flags(t_printf *list, char c);
int				set_modifiers(t_printf *list, const char *restrict format);
int				write_buffer(char (*string)[STR_BUF], t_printf *list,
				int *j, int x);
int				check_colors(char (*string)[STR_BUF],
				const char *restrict format);

#endif
