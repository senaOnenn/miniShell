#include "minishell.h"

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	apply_one_redir(t_redir *redir)
{
	int	fd;

	fd = open_redir_file(redir);
	if (fd < 0)
	{
		perror(redir->file);
		return (1);
	}
	if (redir->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir_lst;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			if (apply_heredoc(redir) != 0)
				return (1);
		}
		else
		{
			if (apply_one_redir(redir) != 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
