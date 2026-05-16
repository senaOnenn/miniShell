#include "minishell.h"

static void	child_process(t_shell *shell, t_cmd *cmd, int in_fd, int fd[2])
{
	char	*path;

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd[0] != -1)
	    close(fd[0]);
	if (apply_redirections(cmd) != 0)
		exit(1);
	if (cmd->is_builtin)
		exit(cmd->builtin_func(cmd->args, &shell->env));
	path = get_cmd_path(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror("minishell");
	free(path);
	exit(126);
}

int	execute_pipeline(t_shell *shell)
{
	int		i;
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	int		status;

	i = 0;
	in_fd = STDIN_FILENO;
	while (i < shell->cmd_count)
	{
		if (i != shell->cmd_count - 1)
			pipe(fd);
		else
		{
			fd[0] = -1;
			fd[1] = STDOUT_FILENO;
		}
		pid = fork();
		if (pid == 0)
			child_process(shell, &shell->cmds[i], in_fd, fd);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
		in_fd = fd[0];
		i++;
	}
	while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            shell->exit_status = 128 + WTERMSIG(status);
    }
	return (shell->exit_status);
}