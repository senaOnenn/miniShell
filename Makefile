NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I parser/include \
			-I LIBFT \
			-I PRINTF \
			-I get_next_line

GNL_SRCS = get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c

SRCS	= 	parser/src/main.c \
			parser/src/lexer.c \
			parser/src/parser.c \
			parser/src/parser_utils.c \
			parser/src/builtin.c \
			$(GNL_SRCS)

OBJ = $(SRCS:.c=.o)

LIBFT = LIBFT/libft.a
PRINTF = PRINTF/libftprintf.a

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT):
	@make -C LIBFT --no-print-directory
 
$(PRINTF):
	@make -C PRINTF --no-print-directory
 
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -lreadline -o $(NAME)
 
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
 
clean:
	@make clean -C LIBFT --no-print-directory
	@make clean -C PRINTF --no-print-directory
	rm -f $(OBJ)
 
fclean: clean
	@make fclean -C LIBFT --no-print-directory
	@make fclean -C PRINTF --no-print-directory
	rm -f $(NAME)
 
re: fclean all
 
.PHONY: all clean fclean re