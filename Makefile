# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 16:09:49 by fvonsovs          #+#    #+#              #
#    Updated: 2023/02/22 16:10:10 by fvonsovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	pipex.a
SRCS		=	pipex.c
INCS		=	pipex.h
OBJS		=	${SRCS:.c=.o}
LIBC		=	ar -cvq
RM			=	rm -f
LIBFT		=	./libft/libft.a

.c.o:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o} -I.

all: $(NAME)

$(NAME): ${OBJS}
	make -C ./libft
	cp ./libft/libft.a ${NAME}
	${LIBC} ${NAME} ${OBJS}

clean: 
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
