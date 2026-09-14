/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:45:59 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 20:46:08 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redir(t_redir **head, t_token **tmp, t_env *env,
	int exit_status)
{
	t_redir	*redir;
	char	*new;

	if (!(*tmp)->next)
		return (syntax_error("newline"), 0);
	if ((*tmp)->next->type != TOKEN_WORD)
		return (syntax_error((*tmp)->next->value), 0);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (free_redirs(*head), 0);
	redir->type = (*tmp)->type;
	redir->was_quoted = (*tmp)->next->quoted;
	redir->file = clean_token((*tmp)->next->value);
	if (redir->was_quoted != 1 && redir->type != REDIR_HEREDOC)
	{
		new = expander(redir->file, redir->was_quoted, env, exit_status);
		if (!new)
			return (free(redir->file), free_redirs(*head), free(redir), 0);
		free(redir->file);
		redir->file = new;
	}
	redir->heredoc_fd = -1;
	redir->next = NULL;
	add_back_redir(head, redir);
	return (*tmp = (*tmp)->next->next, 1);
}

static char	*fill_argv(t_token **tmp, t_env *env, int exit_status)
{
	char	*expanded;
	char	*cleaned;

	expanded = expander((*tmp)->value, (*tmp)->quoted, env, exit_status);
	if (!expanded)
		return (NULL);
	cleaned = clean_token(expanded);
	free(expanded);
	if (!cleaned)
		return (NULL);
	*tmp = (*tmp)->next;
	return (cleaned);
}

static t_cmd	*cmd_malloc(t_token **tmp)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->redirs = NULL;
	command->argv = ft_calloc(count_word_token(*tmp) + 1, sizeof(char *));
	if (!command->argv)
	{
		free(command);
		return (NULL);
	}
	command->next = NULL;
	return (command);
}

static t_cmd	*create_cmd(t_token **tmp, t_env *env, int exit_status)
{
	t_cmd	*cmd;
	char	*exp;
	int		q;
	int		i;

	cmd = cmd_malloc(tmp);
	i = 0;
	while (cmd && *tmp && (*tmp)->type != TOKEN_PIPE)
	{
		q = (*tmp)->quoted;
		if ((*tmp)->type == TOKEN_WORD)
		{
			exp = fill_argv(tmp, env, exit_status);
			if (!exp)
				return (free_one_cmd(cmd), NULL);
			if (q || *exp)
				cmd->argv[i++] = exp;
			else
				free(exp);
		}
		else if (!add_redir(&cmd->redirs, tmp, env, exit_status))
			return (free_one_cmd(cmd), NULL);
	}
	return (cmd);
}

int	parsing(t_token **tokens, t_cmd **head, t_env *env, int exit_status)
{
	t_token	*tmp;
	t_cmd	*new_cmd;

	if (!tokens)
		return (0);
	if ((*tokens)->type == TOKEN_PIPE)
		return (syntax_error("|"), 0);
	tmp = *tokens;
	while (tmp)
	{
		new_cmd = create_cmd(&tmp, env, exit_status);
		if (!new_cmd)
			return (free_cmd(head), 0);
		add_back_cmd(head, new_cmd);
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next)
				return (syntax_error("newline"), free_cmd(head), 0);
			if (tmp->next->type == TOKEN_PIPE)
				return (syntax_error("|"), free_cmd(head), 0);
			tmp = tmp->next;
		}
	}
	return (1);
}
