#include "../include/minishell.h"

/* Pipe sayısını sayarak toplam komut sayısını döndürür */
int	count_cmds(t_token *tokens)
{
	int	count;
 
	count = 1;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static t_redir_type	get_redir_type(t_token_type tok_type)
{
	if (tok_type == TOKEN_LESS)
		return (REDIR_IN);
	if (tok_type == TOKEN_GREAT)
		return (REDIR_OUT);
	if (tok_type == TOKEN_DGREAT)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

int	handle_redir(t_token **tokens, t_cmd *cmd)
{
	t_redir_type	type;
	t_redir			*redir;
	char			*file;

	type = get_redir_type((*tokens)->type); /* Güvenli ve temiz dönüştürme */
	*tokens = (*tokens)->next;              /* Dosya adına geç */
	
	/* Syntax hatası kontrolü (Sadece 2 satır) */
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (print_error("minishell: syntax error near unexpected token\n"));
		
	file = ft_strdup((*tokens)->value);
	if (!file)
		return (1);
		
	redir = new_redir(file, type);
	if (!redir)
	{
		free(file); /* Leak önlemi */
		return (1);
	}
	
	redir_add_back(&cmd->redir_lst, redir);
	return (0);
}

/* Sadece WORD token'larını sayar, yönlendirme ve dosyalarını atlar */
static int	count_words(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		else if (tokens->type >= TOKEN_LESS && tokens->type <= TOKEN_DLESS)
		{
			/* Yönlendirme operatöründen sonraki dosya adını atla */
			if (tokens->next)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (count);
}

/* count_words'ü kullanarak alanı ayırır ve diziyi doldurur */
int	collect_args(t_token *tokens, t_cmd *cmd)
{
	int	i;

	cmd->args = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!cmd->args)
		return (1);
	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(tokens->value);
			if (!cmd->args[i])
				return (1); /* strdup çatlarsa çık, free_cmds bunu temizleyecek */
			i++;
		}
		else if (tokens->type >= TOKEN_LESS && tokens->type <= TOKEN_DLESS)
		{
			if (tokens->next)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	return (0);
}