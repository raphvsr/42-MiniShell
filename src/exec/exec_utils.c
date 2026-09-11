
#include "minishell.h"

int is_buildin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "unset"));
}

int	childs_status(pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)	// wait null = wait any child process still here
		;					// if they is a child process wait
	if (WIFSIGNALED(status))		// if its stopped by something from outside like
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + WTERMSIG(status));	// CTRL C, or a segfault... +128 because its norm of bash
	}
	return (WEXITSTATUS(status));
}

void close_herdocs(t_cmd *cmd)
{
	t_redir *r;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC && r->heredoc_fd != -1) // close herdoc only if it exist (eg the user do CTRL C no need to close it)
			{
				close(r->heredoc_fd);
				r->heredoc_fd = -1;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}
