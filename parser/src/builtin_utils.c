#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	int				i;
	t_builtin_map	map[] = {{"echo", builtin_echo}, {"cd", builtin_cd},
		{"pwd", builtin_pwd}, {"env", builtin_env}, {"export", builtin_export},
		{"unset", builtin_unset}, {"exit", builtin_exit}, {NULL, NULL}};

	if (!cmd)
		return (0);
	i = -1;
	while (map[++i].name)
		if (ft_strncmp(cmd, map[i].name, ft_strlen(map[i].name) + 1) == 0)
			return (1);
	return (0);
}

static int	needs_output(char *cmd)
{
	int			i;
	const char	*list[] = {"echo", "pwd", "env", "export", NULL};

	i = -1;
	while (list[++i])
		if (ft_strncmp(cmd, list[i], ft_strlen(list[i]) + 1) == 0)
			return (1);
	return (0);
}

/* t_cmd'ye doğru builtin fonksiyon pointer'ını atar */
void	set_builtin_func(t_cmd *cmd)
{
	int				i;
	t_builtin_map	map[] = {{"echo", builtin_echo}, {"cd", builtin_cd},
		{"pwd", builtin_pwd}, {"env", builtin_env}, {"export", builtin_export},
		{"unset", builtin_unset}, {"exit", builtin_exit}, {NULL, NULL}};

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	cmd->is_builtin = is_builtin(cmd->args[0]);
	cmd->output_needed = needs_output(cmd->args[0]);
	if (!cmd->is_builtin)
		return ;
	i = -1;
	while (map[++i].name)
	{
		if (ft_strncmp(cmd->args[0], map[i].name, ft_strlen(map[i].name) + 1) == 0)
			cmd->builtin_func = map[i].func;
	}
}