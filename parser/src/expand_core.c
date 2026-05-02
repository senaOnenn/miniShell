#include "../include/minishell.h"

/* Çift tırnak içindeki düz metni ($ veya " görene kadar) koparır */
static char	*get_dquote_plain(char **str)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*str)[len] && (*str)[len] != '$' && (*str)[len] != '"')
		len++;
	temp = ft_substr(*str, 0, len);
	(*str) += len;
	return (temp);
}

/* Çift tırnak içini işler */
static char	*expand_dquote(char **str, t_shell *shell)
{
	char	*result;

	result = ft_strdup("");
	while (**str && **str != '"')
	{
		if (**str == '$')
		{
			(*str)++;
			result = append(result, get_var(str, shell));
		}
		else
		{
			result = append(result, get_dquote_plain(str));
		}
		if (!result)
			return (NULL);
	}
	if (**str == '"')
		(*str)++; /* Kapanış tırnağını atla */
	return (result);
}

/* Tek tırnak içini olduğu gibi alır */
static char	*expand_squote(char **str)
{
	int		len;
	char	*result;
 
	len = 0;
	while ((*str)[len] && (*str)[len] != '\'')
		len++;
	result = ft_substr(*str, 0, len);
	(*str) += len;
	if (**str == '\'')
		(*str)++;
	return (result);
}


/* expand_string'den ayrılan yardımcı: tek bir token parçasını işler */
static char	*expand_chunk(char **str, t_shell *shell)
{
	char	*temp;
	int		len;
 
	if (**str == '"')
	{
		(*str)++;
		return (expand_dquote(str, shell));
	}
	else if (**str == '\'')
	{
		(*str)++;
		return (expand_squote(str));
	}
	else if (**str == '$')
	{
		(*str)++;
		return (get_var(str, shell));
	}
	len = plain_len(*str);
	temp = ft_substr(*str, 0, len);
	(*str) += len;
	return (temp);
}

/* Ana genişletici: tırnak ve $ durumlarını chunk chunk işler */
char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
 
	result = ft_strdup("");
	while (*str)
	{
		result = append(result, expand_chunk(&str, shell));
		if (!result)
			return (NULL);
	}
	return (result);
}