#include "../include/minishell.h"

/* KEY geçerli mi kontrol et (export ile aynı kural) */
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

/* Tek bir argümanı kontrol edip siler, hatalıysa 1 döner */
static int	process_unset(char *arg, char ***env)
{
	if (!valid_key(arg))
	{
		/* Hata mesajı bas ve 1 (başarısız) dön */
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	/* Her şey yolundaysa env'den sil ve 0 dön */
	*env = env_remove(*env, arg);
	return (0);
}

/* unset KEY1 KEY2 ... → env'den sil */
int	builtin_unset(char **args, char ***env)
{
	int	i;
	int	status;

	if (!args[1])
		return (0);
	
	i = 1;
	status = 0;
	while (args[i])
	{
		/* İşçiye gönder, eğer işçi 1 dönerse genel status'u 1 yap */
		if (process_unset(args[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}