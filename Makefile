# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/03/10 21:06:24 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
CC = cc $(CFLAGS)
INC = include/
SRCS = 
SRCS_O = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME) 

$(NAME): $(SRCS_O) $(INC)$(NAME).h
	$(CC) $(NAME).c $(OBJ) -o $(NAME) -I $(INC)

%.o: %.c $(INC)$(NAME).h
	$(CC) -c $< -o $@

=======
#    Updated: 2024/03/12 12:25:40 by aabouqas         ###   ########.fr        #
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
>>>>>>> 45f9038a57dac2cdd4dfb367862b5dc5350165de
clean:
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: clean