
#include "minishell.h"


static int input_handler(t_redir *redir)
{
	int fd;

	if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd < 0)
		{
			perror(redir->file);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (redir->type == REDIR_HEREDOC)
	{
		if (redir->heredoc_fd < 0)
		{
			perror(redir->file);
			return (1);
		}
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
		// TODO: gestion du heredoc qui attend le mot cle
	}
	return (0);
}

static int output_handler(t_redir *redir)
{
	int fd;

	if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(redir->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}

	if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(redir->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}


int exec_redirs(t_redir *redirs)
{
	int status;

	status = 0;
	if (!redirs)
		return (0);
	while (redirs)
	{
		if (redirs->type == REDIR_IN || redirs->type == REDIR_HEREDOC)
		{
			status = input_handler(redirs);
		}
		if (redirs->type == REDIR_OUT || redirs->type == REDIR_APPEND)
		{
			status = output_handler(redirs);
		}
		if (status == 1)
			return (status);
		redirs = redirs->next;
	}
	return (0);
}
