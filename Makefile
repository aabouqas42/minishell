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