#include "../include/minishell.h"

int	expand_args(char **args, t_shell *shell)
{
	int		i;
	char	*new_str;
 
	i = 0;
	while (args && args[i])
	{
		new_str = expand_string(args[i], shell);
		if (!new_str)
            return (1);
		free(args[i]);
		args[i] = new_str;
		i++;
	}
	return (0);
}

int	expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*new_str;
 
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
		{
			new_str = expand_string(redir->file, shell);
			if (!new_str)
				return (1);
			free(redir->file);
			redir->file = new_str;
		}
		redir = redir->next;
	}
	return (0);
}

int	expand_cmds(t_shell *shell)
{
	int	i;
 
	if (!shell || !shell->cmds)
		return (0);
	i = 0;
	while (i < shell->cmd_count)
	{
		if (expand_args(shell->cmds[i].args, shell) != 0)
			return (1);
		if (expand_redirs(shell->cmds[i].redir_lst, shell) != 0)
			return (1);
		i++;
	}
	return (0);
}