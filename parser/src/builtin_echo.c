#include "../include/minishell.h"

/* -n, -nnn, -n -n gibi argümanların geçerli flag olup olmadığını kontrol eder */
static int	is_n_flag(char *arg)
{
	int	i;
 
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}
 
/* echo [-n] [string...] */
int	builtin_echo(char **args, char ***env)
{
	int	i;
	int	newline;
 
	(void)env;
	i = 1;
	newline = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
 