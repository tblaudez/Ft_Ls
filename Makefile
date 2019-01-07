# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/11 17:02:10 by tblaudez          #+#    #+#              #
#    Updated: 2018/11/13 16:26:18 by tblaudez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ls
SRC := src/ft_ls.c src/merge_sort.c src/print_result.c src/utils.c src/utils2.c \
src/utils3.c
OBJ := $(SRC:.c=.o)
LIB := libft/libft.a
INCLUDES := includes/
FLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@printf "\n\e[1;31mCréation du binaire \e[0m- %s\n" $(NAME)
	@gcc $(FLAGS) -I $(INCLUDES) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c
	@printf "\e[1;32mCréation des .o \e[0m- %-50s\r" $@
	@gcc $(FLAGS) -I $(INCLUDES) -o $@ -c $<

$(LIB):
	@make -C libft/

clean:
	@rm -f $(OBJ) && \
	make -C libft/ clean

fclean: clean
	@rm -f $(NAME)  && \
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
