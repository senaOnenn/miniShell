#include "../include/minishell.h"

char	*get_env_value(char *key, char **env)
{
	int	i;
	int	len;
 
	if (!key || !env)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

/* Tırnak veya $ görene kadar normal karakterlerin uzunluğunu say */
int	plain_len(char *str)
{
	int	len;
 
	len = 0;
	while (str[len] && str[len] != '$'
		&& str[len] != '\'' && str[len] != '"')
		len++;
	return (len);
}

/* Değişken adını env'de arar, kopyasını döndürür ve 'name' pointer'ını temizler */
char	*resolve_var_value(char *name, t_shell *shell)
{
	char	*value;

	value = get_env_value(name, shell->env);
	free(name); /* Leak önlemi: name artık işimize yaramıyor */
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/* '$' görünce değişken adını okur ve değerini döndürür */
char	*get_var(char **str, t_shell *shell)
{
	int		len;
	char	*name;

	/* 1. Özel durum: $? (Çıkış kodu) */
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(shell->exit_status));
	}
	
	/* 2. Değişkenin adının uzunluğunu bul */
	len = 0;
	while ((*str)[len] && (ft_isalnum((*str)[len]) || (*str)[len] == '_'))
		len++;
		
	/* 3. Özel durum: Tek başına $ işareti */
	if (len == 0)
	{
		(*str)++;
		return (ft_strdup("$"));
	}
	
	/* 4. İsmi kopar ve yardımcı fonksiyona gönder */
	name = ft_substr(*str, 0, len);
	if (!name)
		return (NULL);
	(*str) += len;
	return (resolve_var_value(name, shell));
}

/* Sonucu güvenli birleştirir: result free olur, tmp caller free eder */
char	*append(char *result, char *temp)
{
	char	*joined;
 
	if (!temp)
		return (free(result), NULL);
	joined = ft_strjoin_free(result, temp);
	free(temp);
	return (joined);
}