Name = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude -ILIBFT -IPRINTF -Iget_next_line

SRC = src/main.c \
	  src/builtin.c \
	  src/lexer.c \
	  src/parser.c \
	  src/parser_utils.c
OBJ = $(SRC:.c=.o)


LIBFT = LIBFT/LIBFT.a
PRINTF = PRINTF/LIBFTPRINTF.a
GNL = get_next_line/get_next_line.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C LIBFT
	@make -C PRINTF
	@make -C get_next_line
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME) -Ireadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C LIBFT
	@make clean -C PRINTF
	@make clean -C get_next_line
	rm -f $(OBJ)

fclean: clean
	@make fclean -C LIBFT
	@make fclean -C PRINTF
	@make fclean -C get_next_line
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re