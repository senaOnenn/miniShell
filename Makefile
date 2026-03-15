Name = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude -Ilibft -Ift_printf -Iget_next_line

SRC = builtin.c lexer.c main.c parser_utils.c parser.c
OBJ = $(SRC:.c=.o)


LIBFT = libft/libft.a
PRINTF = ft_printf/libftprintf.a
GNL = get_next_line/get_next_line.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@make -C ft_printf
	@make -C get_next_line
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C libft
	@make clean -C ft_printf
	@make clean -C get_next_line
	rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@make fclean -C get_next_line
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re