#include "../include/minishell.h"

/* Komutun builtin olup olmadığını kontrol eder */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

/* t_cmd'ye doğru builtin fonksiyon pointer'ını atar */
void	set_builtin_func(t_cmd *cmd)
{
	char	*c;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	c = cmd->args[0];
	cmd->is_builtin = is_builtin(c);
	if (!cmd->is_builtin)
		return ;
	if (ft_strncmp(c, "echo", 5) == 0)
		cmd->builtin_func = builtin_echo;
	else if (ft_strncmp(c, "cd", 3) == 0)
		cmd->builtin_func = builtin_cd;
	else if (ft_strncmp(c, "pwd", 4) == 0)
		cmd->builtin_func = builtin_pwd;
	else if (ft_strncmp(c, "env", 4) == 0)
		cmd->builtin_func = builtin_env;
	else if (ft_strncmp(c, "export", 7) == 0)
		cmd->builtin_func = builtin_export;
	else if (ft_strncmp(c, "unset", 6) == 0)
		cmd->builtin_func = builtin_unset;
	else if (ft_strncmp(c, "exit", 5) == 0)
		cmd->builtin_func = builtin_exit;
}