# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mraspors <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:24:41 by mraspors          #+#    #+#              #
#    Updated: 2022/07/24 22:15:33 by mraspors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIBFT		=	cd libft && make

LIB			=	libft/libft.a

SRC	=   ./src/execution/builtins1.c ./src/execution/builtins2.c\
		./src/execution/start_execution.c ./src/execution/ft_export.c\
		./src/list_env/list_operations.c ./src/list_env/ft_env_list_1.c\
		./src/list_env/ft_env_list_2.c\
		./src/parsing/ft_check_quotes.c ./src/parsing/temp_name.c\
		minishell.c

OBJS	= $(SRC:.c=.o)

GCC	= gcc

FLAGS	= -Wall -Wextra -Werror

HEADER	= philo.h

all:	$(NAME)

$(NAME): $(OBJS)
	$(LIBFT)
	$(GCC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)