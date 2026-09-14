/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:46:16 by kheda             #+#    #+#             */
/*   Updated: 2026/09/11 17:11:33 by p0ubell###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../../libft/libft.h"

void	free_token(t_token **list)
{
	t_token	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	add_back(t_token **list, t_token *new)
{
	t_token	*current;

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

int	find_end_quote(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] != quote && line[*i])
		(*i)++;
	if (!line[*i])
		return (0);
	(*i)++;
	return (1);
}
