#include "../include/minishell.h"

/* KEY=VALUE formatından KEY kısmını döndürür */
static char	*get_key(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

/* KEY geçerli mi kontrol et: harf veya _ ile başlamalı */
static int	valid_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Tek bir argümanı işler, hatalıysa 1 döner */
static int	process_export(char *arg, char ***env)
{
	char	*key;
	char	*value;

	key = get_key(arg);
	if (!valid_key(key))
	{
		/* Bash ile birebir aynı hata mesajı formatı */
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		return (1);
	}
	value = ft_strchr(arg, '=');
	/* Değer ataması varsa env_update ile gönder */
	if (value)
		*env = env_update(*env, key, value + 1);
	free(key);
	return (0);
}

/* export [KEY=VALUE] ... */
int builtin_export(char **args, char ***env)
{
	int i;
	int status;

	/* Argsız kullanım: Alfabetik sırala ve declare -x formatında bas */
	if (!args[1])
		return (print_sorted_env(*env));
	
	i = 1;
	status = 0;
	while (args[i])
	{
		/* Hata gelse bile döngü KIRILMAZ, sadece çıkış kodu (status) 1 olur */
		if (process_export(args[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}