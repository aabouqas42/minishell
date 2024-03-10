<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/10 20:35:56 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

=======
CC = cc
CFLAGS = 
SRC = minishell.c minishell_utils.c
OBJ = $(SRC:%.c=%.o)
NAME = minishell
HEADER = minishell.h
all: $(NAME) $(HEADER)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
>>>>>>> e96513a0ccc6285b5c9e83616c46c06b1b78ecf2
