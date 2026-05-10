#include "../include/minishell.h"

/* Tek bir pipe bölümünü işler, hem args hem redirs doldurulur */
static int	parse_cmd(t_token **tokens, t_cmd *cmd)
{
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		/* Yönlendirme token'ı ise handle_redir'e yolla */
		if ((*tokens)->type >= TOKEN_LESS && (*tokens)->type <= TOKEN_DLESS)
		{
			/* handle_redir zaten pointer'ı ilerleteceği için sadece hata kontrolü yapıyoruz */
			if (handle_redir(tokens, cmd) != 0)
				return (1);
		}
		/* Normal bir kelime (WORD) ise sadece pointer'ı ilerlet */
		else if ((*tokens)->type == TOKEN_WORD)
		{
			*tokens = (*tokens)->next;
		}
		/* Ne WORD ne de YÖNLENDİRME değilse (örneğin arka arkaya iki pipe '||' gelmişse) */
		else
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (1);
		}
	}
	return (0);
}

/* Parametre olarak gelen t_cmd bloğunun içini güvenlice sıfırlar */
void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->args = NULL;
	cmd->redir_lst = NULL;
	cmd->input_fd = 0;   /* Dökümandaki kural: STDIN default */
	cmd->output_fd = 1;  /* Dökümandaki kural: STDOUT default */
	cmd->is_builtin = 0;
	cmd->builtin_func = NULL;
}

/* Komutları dolduran ve hataları yöneten yardımcı fonksiyon */
static int	fill_cmd_array(t_cmd *cmds, t_token *tok, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		init_cmd(&cmds[i]); /* malloc yerine sadece değerleri sıfırla (Leak Önlemi) */
		if (collect_args(tok, &cmds[i]) != 0 || parse_cmd(&tok, &cmds[i]) != 0)
		{
			free_cmds(cmds, i + 1);
			return (1); /* Hata varsa 1 dön */
		}
		set_builtin_func(&cmds[i]); /* Executor için builtin işaretle */
		if (tok && tok->type == TOKEN_PIPE)
			tok = tok->next; /* Pipe'ı atla */
		i++;
	}
	return (0);
}

/* Ana parser fonksiyonu */
t_cmd	*parser(t_token *tokens, char **env)
{
	t_cmd	*cmds;
	int		count;

	(void)env;
	if (!tokens)
		return (NULL);
	count = count_cmds(tokens);
	cmds = malloc(sizeof(t_cmd) * count);
	if (!cmds)
		return (NULL);
	if (fill_cmd_array(cmds, tokens, count) != 0)
		return (NULL); /* Yardımcı fonksiyonda hata (malloc vb.) çıkarsa NULL dön */
	return (cmds);
}