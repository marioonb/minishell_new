# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelorge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 15:42:13 by mbelorge          #+#    #+#              #
#    Updated: 2020/11/22 15:42:16 by mbelorge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	main.c \
		srcs/parse.c \
		srcs/ft_error.c \
		srcs/echo.c \
		srcs/builtin.c \
		srcs/utils.c \
		srcs/check_errors.c \
		srcs/env.c \
		srcs/pwd.c \
		srcs/export.c \
		srcs/cd.c \
		srcs/unset.c \
		srcs/split_minishell.c \
		srcs/split_space.c \
		srcs/tab_env_utils.c \
		srcs/tab_export_utils.c \
		srcs/exit.c

OBJ = main.o \
		parse.o \
		ft_error.o \
		echo.o \
		builtin.o \
		utils.o \
		check_errors.o \
		env.o \
		pwd.o \
		export.o \
		cd.o \
		unset.o \
		split_minishell.o \
		split_space.o \
		tab_env_utils.o \
		tab_export_utils.o \
		exit.o

FLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

LIB = ./libft/libft.a

all: $(NAME)

$(NAME):
	@make -C libft/ libft.a
	gcc $(FLAGS) -c $(SRC) -g
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

libft:
	make -C libft/ libft.a

clean:
	make -C libft/ clean
	rm -fr $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -fr $(NAME)

re: fclean all
