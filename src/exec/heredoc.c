#include "minishell.h"



int read_heredoc(t_redir *redir)
{
	char *line;
	int fd[2];

	if (pipe(fd) ==  -1)
	{
		perror("minishell: heredoc pipe");
		return (1);
	}
	while (1)
	{
		if (g_signal == SIGINT)
		{
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		line = readline("> ");
		if (line == NULL)
		{
			err_warn(redir->file, ": warning: here-document"
				"delimited by end-of-file (wanted `",
				"')");
			break;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	return (0);
}

int heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		t_redir *curr_redir;

		curr_redir = cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == REDIR_HEREDOC)
			{
				if (!curr_redir->file)
					return(write(2, "minishell: syntax error near"
						" unexpected token `newline'", 56), 1);
				if (read_heredoc(curr_redir) != 0)
					return (1);
			}
			curr_redir = curr_redir->next;
		}
		cmd = cmd->next;
	}
	return 0;
}
