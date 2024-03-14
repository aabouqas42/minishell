# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/14 22:55:19 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS =
CC = cc $(CFLAGS)
INC = include/
LIBFT = libft/libft.a
SRCS = 	parsing/command_check.c \
		utils/minishell_utils.c \
		builtins/cd.c builtins/echo.c builtins/pwd.c
SRCS_O = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(NAME).c $(SRCS_O) $(INC)$(NAME).h $(LIBFT)
	$(CC) $(NAME).c $(SRCS_O) $(LIBFT) -lreadline -o $(NAME) 

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
