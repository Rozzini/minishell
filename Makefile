# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mraspors <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:24:41 by mraspors          #+#    #+#              #
#    Updated: 2022/10/27 20:23:11 by mraspors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

MAKE = make

CC = gcc

CFLAG = -Wall -Werror -Wextra -g

LIBFTDIR = ./libft

LIBFT_A = ./libft/libft.a

SRC	=   ./src/execution/builtins1.c ./src/execution/builtins2.c\
	./src/execution/start_execution.c ./src/execution/ft_export.c\
	./src/list_env/list_operations.c ./src/list_env/ft_env_list_1.c\
	./src/list_env/env_list_to_string.c ./src/parsing/ft_check_quotes.c\
	./src/parsing/temp_name.c ./src/parsing/expansion.c ./src/parsing/basic_parsing.c\
	./src/parsing/builtins_parser.c ./src/parsing/start_parsing.c ./src/parsing/parsing_helpers.c\
	./src/helpers/free.c ./src/parsing/pipes_parsing.c\
	./src/redirection/rdr_utils.c ./src/redirection/redirection.c\
	./src/pipes/pipes.c  minishell.c

HEADER	= minishell.h

OBJ	= $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

.c.o: $(HEADER)
		$(CC) $(CFLAG) -c $< -o $(<:.c=.o) 

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAG) $(SRC) $(LIBFT_A) -o $(NAME) -lreadline && clear

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJ) && clear

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME) && clear

re: fclean all

.PHONY: all clean fclean re