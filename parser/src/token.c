#include "../include/minishell.h"

/* Yeni token oluşturur, value zaten malloc'lu gelir (ft_substr/ft_strdup) */
t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value); /* value malloc'lu geldi, token oluşamazsa free et */
		return (NULL);
	}
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

/* Token'ı listenin sonuna ekler */
void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


/* Debug: token listesini ekrana yazdırır */
void	print_tokens(t_token *list)
{
	char	*types[] = {"WORD", "PIPE", "LESS", "GREAT", "DGREAT", "DLESS"};

	while (list)
	{
		ft_putstr_fd("[", 1);
		ft_putstr_fd(types[list->type], 1);
		if (list->value)
		{
			ft_putstr_fd(":", 1);
			ft_putstr_fd(list->value, 1);
		}
		ft_putstr_fd("] ", 1);
		list = list->next;
	}
	ft_putchar_fd('\n', 1);
}