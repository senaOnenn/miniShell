#include "../include/minishell.h"

/* KEY varsa günceller, yoksa sona ekler. Yeni dizi döndürür. */
char	**env_update(char **env, char *key, char *value)
{
	char	**new_env;
	int		size;
	int		i;

	if (update_existing(env, key, value))
		return (env);
	size = env_size(env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (i < size)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = make_entry(key, value);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

/* KEY'i env'den siler. Yeni dizi döndürür. */
char	**env_remove(char **env, char *key)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;

	if (!env || !key)
		return (env);
	len = ft_strlen(key);
	new_env = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (is_env_match(env[i], key, len))
			free(env[i]);
		else
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}