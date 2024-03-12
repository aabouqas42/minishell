# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/12 17:39:46 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -lreadline
CC = cc $(CFLAGS)
INC = include/
LIBFT = libft/libft.a
SRCS = parsing/command_check.c utils/minishell_utils.c
SRCS_O = $(SRCS:%.c=%.o)
NAME = minishell

all: $(NAME)

$(NAME): $(SRCS_O) $(NAME).c $(INC)$(NAME).h $(LIBFT)
	$(CC) $(NAME).c $(SRCS_O) $(LIBFT) -o $(NAME)

%.o: %.c $(INC)$(NAME).h
	$(CC) -c $< -o $@

$(LIBFT): 
	make -C libft/

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean 
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
