/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:46:37 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 20:29:13 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
			close(redir->heredoc_fd);
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free_argv((*cmd)->argv);
		free_redirs((*cmd)->redirs);
		free(*cmd);
		*cmd = tmp;
	}
}

void	add_back_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*current;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_back_redir(t_redir **list, t_redir *new)
{
	t_redir	*current;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}
