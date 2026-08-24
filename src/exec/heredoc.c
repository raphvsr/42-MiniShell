#include "minishell.h"

   

int read_heredoc(t_redir *redir)
{
	char *line;
	int fd[2];

	while (1)
	{
		if (g_signal == SIGINT)
		{
			// TODO
			return (1);
		}
		line = readline("> ");
		if (line == NULL)
		{
			err_warn(redir->file, ": warning: here-document at line 3"
				"delimited by end-of-file (wanted `",
				"')");
			break;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break;
		}
	}
}

int heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		t_redir *curr_redir;
		while (curr_redir)
		{
			if (curr_redir->type == REDIR_HEREDOC)
				if (!curr_redir->file)
					return(write(2, "minishell: syntax error near"
						" unexpected token `newline'", 59), 1);
				read_heredoc(curr_redir);
			curr_redir = curr_redir->next;
		}
		cmd = cmd->next;
	}

}
