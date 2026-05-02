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
			parser/src/lexer_utils.c \
			parser/src/parser.c \
			parser/src/parser_utils.c \
			parser/src/parser_build.c \
			parser/src/free_utils.c \
			parser/src/expand.c \
			parser/src/expand_utils.c \
			parser/src/expand_core.c \
			parser/src/error.c \
			parser/src/builtin_unset.c \
			parser/src/builtin_pwd.c \
			parser/src/builtin_exp.c \
			parser/src/builtin_exit.c \
			parser/src/builtin_env.c\
			parser/src/builtin_echo.c \
			parser/src/builtin_cd.c \
			parser/src/builtin_utils.c \
			parser/src/env_utils_0.c \
			parser/src/env_utils_1.c \
			parser/src/token.c \
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