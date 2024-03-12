# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/12 15:21:02 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = 
SRC = minishell.c utils/minishell_utils.c 
OBJ = $(SRC:%.c=%.o)
NAME = minishell
HEADER = headers/minishell.h
LIBFT = libft/libft.a
all: $(NAME) $(HEADER)

$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -I headers -lreadline -o $(NAME)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I headers -lreadline -c $< -o $@
$(LIBFT):
	make -C libft
fclean: clean
	rm -f $(NAME)
clean:
	rm -f $(OBJ)

re: fclean all