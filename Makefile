# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/12 18:21:31 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -lreadline
CC = cc $(CFLAGS)
INC = include/
LIBFT = libft/libft.a
SRCS = parsing/command_check.c quick_utils/free_adv.c
SRCS_O = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(NAME).c $(SRCS_O) $(INC)$(NAME).h $(LIBFT)
	$(CC) $(NAME).c $(SRCS_O) $(LIBFT) -o $(NAME)

%.o: %.c $(INC)$(NAME).h
	$(CC) -c $< -o $@

$(LIBFT): 
	make -C libft/

clean:
	make -C libft/ clean
	rm -f $(SRCS_O)

fclean: clean 
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
