/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 14:21:24 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/14 14:28:42 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	connect_cpipe(t_cmd *cmd, t_env **env_list, int *fds, int status)
{
	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (cmd->next)
	{
		close(fds[1]);
		dup2(fds[2], STDOUT_FILENO);
		close(fds[2]);
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

static void	update_pipe(int *fds, int *pipe_fd, int has_next)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (has_next)
	{
		close(pipe_fd[1]);
		fds[0] = pipe_fd[0];
	}
}

int	exec_pipe(t_cmd *cmd, t_env **env_list, int status)
{
	int		pipe_fd[2];
	int		fds[3];
	pid_t	pid;

	fds[0] = -1;
	init_signals_exec();
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (1);
		fds[1] = pipe_fd[0];
		fds[2] = pipe_fd[1];
		pid = fork();
		if (pid == 0)
			connect_cpipe(cmd, env_list, fds, status);
		update_pipe(fds, pipe_fd, cmd->next != NULL);
		cmd = cmd->next;
	}
	status = childs_status(pid);
	return (init_signals(), status);
}
