# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mraspors <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:24:41 by mraspors          #+#    #+#              #
#    Updated: 2022/11/16 18:03:02 by mraspors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

MAKE = make

CC = gcc


LIBFTDIR = ./libft

LIBFT_A = ./libft/libft.a

prefix		=	/usr/local/Cellar/readline/8.1
# prefix		=	/opt/homebrew/Cellar/readline/8.1.2

exec_prefix	=	${prefix}

libdir		=	${exec_prefix}/lib

includedir	=	${prefix}/include

CFLAG = -Wall -Werror -Wextra -g3 -I${includedir}

LDFLAGS 	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib

LDFLAGS 	=	-lreadline -L${libdir}

SRC	=   ./src/execution/builtins_parent.c ./src/execution/builtins_child.c\
	./src/execution/start_execution.c ./src/execution/ft_export.c\
	./src/list/list_operations.c ./src/list/ft_env_list_1.c\
	./src/list/env_list_to_string.c ./src/parsing/ft_check_quotes.c\
	./src/execution/minihell_call.c ./src/parsing/expansion.c\
	./src/parsing/expansion_helpers.c ./src/parsing/basic_parsing.c\
	./src/parsing/builtins_parser.c ./src/parsing/start_parsing.c\
	./src/parsing/parsing_helpers.c ./src/redirection/heredog.c\
	./src/helpers/free1.c ./src/helpers/free2.c ./src/helpers/print_structs.c\
	./src/parsing/pipes_parsing.c ./src/redirection/rdr_utils.c\
	./src/pipes/pipes.c ./src/pipes/pipes_helper.c ./src/redirection/redirection.c\
	./src/signals/signals.c ./src/list/rdr_cmd_helpers.c minishell.c

HEADER	= minishell.h

OBJ	= $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

.c.o: $(HEADER)
		$(CC) $(CFLAG) -c $< -o $(<:.c=.o) 

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAG) $(SRC) $(LIBFT_A) -o $(NAME) $(LDFLAGS) && clear

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJ) && clear

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME) && clear

re: fclean all

.PHONY: all clean fclean re