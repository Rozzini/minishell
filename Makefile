# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mraspors <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:24:41 by mraspors          #+#    #+#              #
#    Updated: 2022/07/22 20:44:42 by mraspors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIBFT		=	cd libft && make

LIB			=	libft/libft.a

SRC	= minishell.c

OBJS	= $(SRC:.c=.o)

GCC	= gcc

FLAGS	= -Wall -Wextra -Werror

HEADER	= philo.h

all:	$(NAME)

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)