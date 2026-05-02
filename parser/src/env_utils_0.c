#include "../include/minishell.h"

/* env dizisinin eleman sayısını döndürür */
int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/* envp'yi kopyalar, yeni malloc'lu dizi döndürür */
char	**env_copy(char **envp)
{
	char	**copy;
	int		i;

	if (!envp)
		return (NULL);
	copy = malloc(sizeof(char *) * (env_size(envp) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < env_size(envp))
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			free_array(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/* "KEY=VALUE" formatında yeni eleman oluşturur */
char	*make_entry(char *key, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	return (entry);
}

/* KEY eşleşiyor mu ve '=' veya '\0' ile mi bitiyor kontrolü */
int	is_env_match(char *env_str, char *key, int len)
{
	if (ft_strncmp(env_str, key, len) == 0)
	{
		/* Bash tuzağı çözümü: Sadece '=' değil, '\0' da geçerlidir */
		if (env_str[len] == '=' || env_str[len] == '\0')
			return (1);
	}
	return (0);
}

/* KEY varsa günceller, 1 döner. Yoksa 0 döner. */
int	update_existing(char **env, char *key, char *value)
{
	char	*entry;
	int		len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (env && env[i])
	{
		if (is_env_match(env[i], key, len))
		{
			entry = make_entry(key, value);
			if (entry)
			{
				free(env[i]);
				env[i] = entry;
			}
			return (1);
		}
		i++;
	}
	return (0);
}