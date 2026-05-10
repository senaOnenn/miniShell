#include "minishell.h"

static int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (1);
	if (apply_redirections(cmd) != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		shell->exit_status = 1;
		return (1);
	}
	status = cmd->builtin_func(cmd->args, &shell->env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	shell->exit_status = status;
	return (status);
}

static int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = get_cmd_path(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		shell->exit_status = 127;
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (apply_redirections(cmd) != 0)
		{
			free(path);
			exit(1);
		}
		execve(path, cmd->args, shell->env);
		perror("minishell");
		free(path);
		exit(126);
	}
	waitpid(pid, &status, 0);

	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			shell->exit_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putendl_fd("Quit", 1);
			shell->exit_status = 131;
		}
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	free(path);
	return (shell->exit_status);
}

int	execute_single(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->is_builtin)
		return (execute_builtin(shell, cmd));
	return (execute_external(shell, cmd));
}

int	execute_shell(t_shell *shell)
{
	if (!shell || !shell->cmds)
		return (1);
	if (shell->cmd_count == 1)
		return (execute_single(shell, &shell->cmds[0]));
	return (0);
}