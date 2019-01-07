# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 15:48:20 by tblaudez          #+#    #+#              #
#    Updated: 2018/08/20 19:06:47 by tblaudez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRC := ft_atoi.c ft_memcpy.c ft_strncat.c ft_bzero.c ft_memmove.c ft_strncmp.c \
ft_isalnum.c ft_memset.c ft_strncpy.c ft_isalpha.c ft_strcat.c ft_strnstr.c \
ft_isascii.c ft_strchr.c ft_strrchr.c ft_isdigit.c ft_strcmp.c ft_strstr.c \
ft_isprint.c ft_strcpy.c ft_memccpy.c ft_strdup.c \
ft_memchr.c ft_strlcat.c ft_memcmp.c ft_strlen.c ft_memalloc.c ft_memdel.c \
ft_strnew.c ft_strdel.c ft_strclr.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strsplit.c \
ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstbackadd.c \
ft_isspace.c ft_str_is_something.c \
ft_islower.c ft_isupper.c ft_strndup.c \
ft_charsrc.c ft_charnsrc.c ft_printf_libft/ft_printf.c \
ft_printf_libft/print_letters.c ft_printf_libft/print_numbers.c \
ft_printf_libft/utils.c ft_printf_libft/utils2.c ft_nbrdig.c ft_atoibase.c \
ft_strreplace.c ft_power.c ft_strjoinfree.c ft_charrsrc.c ft_itoabase.c \
ft_strreplace_all.c ft_strarray_new.c ft_strarray_del.c \
ft_setintarray.c ft_strarraylen.c ft_putstrarray.c ft_lstlen.c ft_strtrim.c \
ft_strtrimchar.c ft_lstget.c get_next_line.c
OBJ := $(SRC:.c=.o)
INCLUDES := includes/

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	@printf "\n\e[1;33mCréation du binaire \e[0m- %s\n" $(NAME)
	@ar rc $(NAME) $(OBJ) \
	&& ranlib $(NAME)

%.o : %.c
	@printf "\e[1;32mCréation des .o \e[0m- %-50s\r" $@
	@gcc -Wall -Wextra -Werror -I $(INCLUDES) -o $@ -c $<

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
