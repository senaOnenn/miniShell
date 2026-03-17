#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

#include "../LIBFT/LIBFT.h"
#include "../PRINTF/PRINTF.h"

/*
** Token türleri
** Lexer inputu bu tiplere ayıracak
*/
typedef enum e_token_type
{
	T_WORD,        // normal kelime (ls, echo, file.txt)
	T_PIPE,        // |
	T_REDIR_IN,    // <
	T_REDIR_OUT,   // >
	T_APPEND,      // >>
	T_HEREDOC      // <<
}	t_token_type;

/*
** Token linked list
*/
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

/* lexer */
t_token	*lexer(char *input);

/* parser */
void	parser(t_token *tokens);

/* utils */
t_token	*new_token(char *value, t_token_type type);
void	add_token(t_token **list, t_token *new);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token **list);
int is_whitespace(char c);
int	is_special_char(char c);
t_token	*token_last(t_token *token);
int	ft_token_size(t_token *token);
int	is_quote(char c);


#endif