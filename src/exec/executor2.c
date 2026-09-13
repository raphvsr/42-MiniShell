#include "minishell.h"

int	exec_one_builtin(t_cmd *cmd, t_env **env_list, int status)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	if (exec_redirs(cmd->redirs) != 0)
		status = 1;
	else
		status = execute_builtin(cmd, env_list, status);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (status);
}

static void	connect_cpipe(t_cmd *cmd, t_env **env_list, int prev_fd,
	int *pipe_fd, int status)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	init_csignals();
	if (exec_redirs(cmd->redirs) != 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_buildin(cmd->argv[0]))
		exit(execute_builtin(cmd, env_list, status));
	cprocess(f_cmdpath(cmd->argv[0], *env_list), cmd, env_to_array(*env_list));
}

int	exec_pipe(t_cmd *cmd, t_env **env_list, int status)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	init_signals_exec();
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (1);
		pid = fork();
		if (pid == 0)
			connect_cpipe(cmd, env_list, prev_fd, pipe_fd, status);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	status = childs_status(pid);
	return (init_signals(), status);
}
