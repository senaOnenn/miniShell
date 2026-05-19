#include "../include/minishell.h"

/* Sıralanmış listeyi 'declare -x KEY="VALUE"' formatında ekrana basar */
static void	print_declare(char **env)
{
	int		i;
	char	*val;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		val = ft_strchr(env[i], '=');
		if (val)
		{
			/* Eşittir işaretine kadar olan KEY kısmını bas */
			write(1, env[i], val - env[i] + 1);
			/* VALUE kısmını tırnak içine alarak bas */
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(val + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd(env[i], 1);
		i++;
	}
}

/* env dizisini kopyalar, alfabetik sıralar ve ekrana basar */
int	print_sorted_env(char **env)
{
	char	**cp;
	char	*tmp;
	int		i;
	int		j;

	cp = env_copy(env); /* env_utils.c içindeki strdup yapan kopyalayıcımız */
	if (!cp)
		return (1);
	i = -1;
	while (cp[++i])
	{
		j = i;
		while (cp[++j])
		{
			/* ASCII değerlerine göre alfabetik sıralama (Bubble Sort) */
			if (ft_strncmp(cp[i], cp[j], ft_strlen(cp[i]) + 1) > 0)
			{
				tmp = cp[i];
				cp[i] = cp[j];
				cp[j] = tmp;
			}
		}
	}
	print_declare(cp);
	free_array(cp); /* Kopyalanan diziyi ve içindeki stringleri temizle */
	return (0);
}