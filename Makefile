# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mraspors <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:24:41 by mraspors          #+#    #+#              #
#    Updated: 2022/07/22 18:26:23 by mraspors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIBFT		=	cd libft && make

LIB			=	libft/libft.a

SRC	= minishell.c

OBJS	= $(SRC:.c=.o)

GCC	= gcc -g3

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -lpthread

HEADER	= philo.h

all:	$(NAME)

$(NAME): $(OBJS)
	$(GCC) -pthread $(FLAGS) $(OBJS) $(LIB) -o $(NAME) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)