/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:45:59 by kheda             #+#    #+#             */
/*   Updated: 2026/09/12 14:52:38 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../../libft/libft.h"

static int	add_redirs(t_redir **head, t_token **tmp)
{
	t_redir	*redirs;

	while (*tmp && (*tmp)->type != TOKEN_WORD && (*tmp)->type != TOKEN_PIPE)
	{
		if (!(*tmp)->next || (*tmp)->next->type != TOKEN_WORD)
			return (free_redirs(*head), 0);
		redirs = malloc(sizeof(t_redir));
		if (!redirs)
			return (free_redirs(*head), 0);
		redirs->type = (*tmp)->type;
		redirs->was_quoted = (*tmp)->next->quoted;
		redirs->file = clean_token((*tmp)->next);
		redirs->heredoc_fd = -1;
		redirs->next = NULL;
		add_back_redir(head, redirs);
		*tmp = (*tmp)->next->next;
	}
	return (1);
}

static char	**fill_argv(t_token **tmp)
{
	char	**argv;
	int		i;
	int		len;
	char	*s;

	len = count_word_token(*tmp);
	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < len && *tmp)
	{
		s = clean_token(*tmp);
		if (!s)
		{
			argv[i] = NULL;
			return (free_argv(argv), NULL);
		}
		argv[i] = s;
		*tmp = (*tmp)->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_cmd	*create_cmd(t_token **tmp)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->redirs = NULL;
	command->argv = fill_argv(tmp);
	if (!(command)->argv)
	{
		free(command);
		command = NULL;
		return (NULL);
	}
	if (!add_redirs(&command->redirs, tmp))
	{
		free_argv(command->argv);
		free(command);
		command = NULL;
		return (NULL);
	}
	command->next = NULL;
	return (command);
}

int	parsing(t_token **tokens, t_cmd **head)
{
	t_token	*tmp;
	t_cmd	*new_cmd;

	if (!tokens || (*tokens)->type == TOKEN_PIPE)
		return (0);
	tmp = *tokens;
	while (tmp)
	{
		new_cmd = create_cmd(&tmp);
		if (!new_cmd)
			return (free_cmd(head), 0);
		add_back_cmd(head, new_cmd);
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!(tmp->next) || tmp->next->type == TOKEN_PIPE)
				return (free_cmd(head), 0);
			tmp = tmp->next;
		}
	}
	return (1);
}
