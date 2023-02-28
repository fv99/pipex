# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 16:09:49 by fvonsovs          #+#    #+#              #
#    Updated: 2023/02/28 16:06:44 by fvonsovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
NAME		=	pipex
SRCS		=	main.c pipex.c pipex_utils.c
INCS		=	pipex.h
OBJS		=	${SRCS:.c=.o}
LIBC		=	ar -cvq
RM			=	rm -f
LIBFT		=	./libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I. -I./libft

all: $(NAME)

$(NAME): ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

clean: 
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
