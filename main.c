#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	init_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->cmd_count = 0;
	shell->env = env_copy(envp);
	shell->exit_status = 0;
	shell->signal_received = 0;
}

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;

	tokens = lexer(line);
	if (!tokens)
		return ;
	shell->cmd_count = count_cmds(tokens);
	shell->cmds = parser(tokens, shell->env);
	free_tokens(tokens);
	if (!shell->cmds)
		return ;
	expand_cmds(shell);
	execute_shell(shell);
	free_cmds(shell->cmds, shell->cmd_count);
	shell->cmds = NULL;
	shell->cmd_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*line)
		{
			add_history(line);
			process_line(line, &shell);
		}
		free(line);
	}
	free_array(shell.env);
	rl_clear_history();
	return (shell.exit_status);
}