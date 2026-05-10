#include "../include/minishell.h"

/* env → tüm environment değişkenlerini KEY=VALUE formatında yaz */
int	builtin_env(char **args, char ***env)
{
	int	i;

	/* Kural: Argüman almamalı */
	if (args && args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	if (!env || !*env)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		/* Bash kuralı: Sadece değeri olanları ('=' içerenleri) yazdır */
		if (ft_strchr((*env)[i], '='))
			ft_putendl_fd((*env)[i], 1);
		i++;
	}
	return (0);
}