/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 13:54:28 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/14 15:26:49 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hcheck(char *line, t_redir *redir)
{
	if (line == NULL)
	{
		err_warn(redir->file, ": warning: here-document "
			"delimited by end-of-file (wanted `",
			"')");
		return (1);
	}
	if (ft_strcmp(line, redir->file) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	hloop(t_redir *redir, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		if (hcheck(line, redir))
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	return (0);
}

int	read_heredoc(t_redir *redir)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("minishell: heredoc pipe"), 1);
	if (hloop(redir, fd) != 0)
		return (1);
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	t_redir	*curr_redir;

	while (cmd)
	{
		curr_redir = cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == REDIR_HEREDOC)
			{
				if (!curr_redir->file)
					return (err_warn("syntax error near "
							"unexpected token ", curr_redir->file, ""), 1);
				if (read_heredoc(curr_redir) != 0)
					return (1);
			}
			curr_redir = curr_redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
