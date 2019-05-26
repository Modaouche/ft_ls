# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2018/11/06 03:03:03 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC =  	srcs/main.c\
		srcs/ft_exit.c\
		srcs/ft_util.c\
		srcs/ft_util2.c\
		srcs/ft_ls.c\
		srcs/ft_tree.c\
		srcs/ft_filling.c\
		srcs/ft_stat.c\
		srcs/ft_stat2.c\
		srcs/ft_to_sort.c\
		srcs/ft_to_sort2.c\
		srcs/for_bonus.c\
		srcs/for_bonus2.c\
		srcs/for_bonus3.c\
		srcs/ft_opt1.c\
		srcs/ft_opt2.c\
		srcs/ft_opt3.c\
		srcs/ft_print.c

LIB = srcs/libft/libft.a\
      srcs/libft/ft_printf/libftprintf.a\

OBJ = $(SRC:.c=.o)

DIRPRINTF = srcs/libft/ft_printf/src\
			srcs/libft/ft_printf/includes\
			srcs/libft/ft_printf/src/libft

INCLUDES = srcs/libft/ft_printf/includes/ft_conv.h\
		   srcs/libft/ft_printf/includes/ft_printf.h\
		   srcs/libft/libft.h\
		   includes/ft_ls.h\
		   includes/ft_opt.h\

LIBFT = srcs/libft

LIBFTPRINTF = srcs/libft/ft_printf/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Isrcs 
#		 -g -fsanitize=address\
		 -fno-omit-frame-pointer\
		 -fsanitize-address-use-after-scope \



all: $(NAME)

$(NAME): $(OBJ) Makefile $(INCLUDES) $(LIBFT) $(LIBFTPRINTF) $(DIRPRINTF) srcs/libft/ft_printf/Makefile
	make -C $(LIBFT) all
	make -C $(LIBFTPRINTF) all
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT)
	make clean -C $(LIBFTPRINTF)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	make fclean -C $(LIBFTPRINTF)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)

re: fclean all
