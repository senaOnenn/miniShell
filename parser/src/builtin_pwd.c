#include "../include/minishell.h"
 
/* pwd → bulunduğu dizini yaz */
int	builtin_pwd(char **args, char ***env)
{
	char	cwd[4096];
 
	(void)args;
	(void)env;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("minishell: pwd: error\n", 2);
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	return (0);
}
 