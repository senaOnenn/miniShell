#include "../include/minishell.h"

/* Çift yıldız (**) kullanıyoruz çünkü string'in içindeki konumumuzu 
   gerçekten ileri sarmak istiyoruz. */
void	skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

static int get_info(char *str, t_token_type *form)
{
    if (ft_strncmp(str, "<<", 2) == 0)
		*form = TOKEN_DLESS;
	else if (ft_strncmp(str, ">>", 2) == 0)
		*form = TOKEN_DGREAT;
	else if (*str == '<')
		*form = TOKEN_LESS;
	else if (*str == '>')
		*form = TOKEN_GREAT;
	else if (*str == '|')
		*form = TOKEN_PIPE;
	else
		return (0); /* Operatör değilse uzunluk 0 döner */
		
	if (*form == TOKEN_DLESS || *form == TOKEN_DGREAT)
		return (2); /* Çift karakterli ise 2 byte */
	return (1);     /* Tek karakterli ise 1 byte */
}

int	handle_operator(char **line, t_token **list)
{
   	t_token_type	type;
	int				len;
	t_token			*new;
	char 			*tmp_str;
  
	len = get_info(*line, &type);
	if (len == 0)
		return (0);
	tmp_str = ft_substr(*line,0,len);
	if (!tmp_str)
		return(1);
	/* Önce token'ı oluştur, başarılıysa pointer'ı ilerlet */
	new = new_token(tmp_str, type);
	if(!new)
	{
		free(tmp_str);
		return(1);
	}
	(*line) += len;
	token_add_back(list, new);
	return (0);
}

static int word_len(char *str)
{
    int len;
    char quote;

    len = 0;
    quote = 0;
    while(str[len])
    {
        /* 1. Eğer tırnak dışındaysak ve yeni bir tırnak açılırsa, state'i güncelle */
		if (quote == 0 && (str[len] == '\'' || str[len] == '"'))
			quote = str[len];
		/* 2. Eğer tırnak içindeysek ve KENDİ tırnağımızı tekrar görürsek, state'i sıfırla (kapat) */
		else if (quote != 0 && str[len] == quote)
			quote = 0;
		/* 3. Eğer tırnak dışındaysak ve kelimeyi bitiren bir şeye (boşluk veya operatör) rastlarsak, dur */
		else if (quote == 0 && (str[len] == ' ' || str[len] == '\t'
				|| str[len] == '|' || str[len] == '<' || str[len] == '>'))
			break ;
		len++;
    }
    /* Döngü bittiğinde hala bir tırnak açıksa (quote != 0), bu bir hatadır */
	if (quote != 0)
		return (-1);
	return (len);
}

int handle_word(char **line, t_token **list)
{
    int		len;
	char	*word;
	t_token	*new;

	len = word_len(*line);
	if (len == -1)
		return (print_error("minishell: unexpected EOF while looking for matching quote\n"));
	if (len == 0)
		return (0);
	word = ft_substr(*line, 0, len);
	if (!word)
		return (1);
	new = new_token(word, TOKEN_WORD);
	if (!new)
	{
		free(word); 
		return (1);
	}
	token_add_back(list, new);
	(*line) += len; 
	return (0);
}