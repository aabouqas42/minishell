# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/16 16:34:19 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS =
CC = cc $(CFLAGS)
INC = include/
LIBFT = libft/libft.a
SRCS = 	parsing/command_check.c \
		utils/minishell_utils.c utils/ft_split.c \
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