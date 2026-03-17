#include "../include/minishell.h"

/*
** Yeni bir token oluşturur ve içeriğini doldurur.
** ft_strdup kullanarak değeri kopyalamak, input stringi değişse bile
** tokenın verisini korumamızı sağlar.
*/
t_token	*new_token(char *value, t_token_type type)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if(!new)
        return (NULL);
    new->value = ft_strdup(value);
    new->type = type;
    new->next = NULL;
    return(new);
}
/*
** Listenin sonuna yeni bir token ekler.
*/
void add_token(t_token **list, t_token *new)
{
    t_token *temp;
    if(!list || !new)
        return;
    if(!*list)
    {
        *list = new;
        return;
    }
    temp = *list;
    while(temp->next)
        temp = temp-next;
    temp->next = new;
}

/*
** Debug amaçlı: Token listesini ekrana basar.
*/
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Token: [%s] | Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}
/*
** Bellek sızıntısını önlemek için listeyi serbest bırakır.
*/
void	free_tokens(t_token **list)
{
	t_token	*temp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->value);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

/*
** WHITESPACE KONTROLÜ
** Lexer'da bir kelimenin bittiğini veya boşlukları atlamamız 
** gerektiğini anlamak için kullanılır. Standard ASCII boşluklarını kontrol eder.
*/
int is_whitespace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

/*
** ÖZEL KARAKTER KONTROLÜ
** Bir karakterin pipe (|) veya yönlendirme (<, >) olup olmadığını anlarız.
** Bu karakterler gördüğümüzde mevcut kelimeyi bitirip yeni bir token başlatırız.
*/
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}