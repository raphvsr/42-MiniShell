/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:46:04 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 20:46:46 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

int	sym(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

int	count_word_token(t_token *tmp)
{
	int	cpt;

	cpt = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
		{
			cpt++;
			tmp = tmp->next;
		}
		else
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
				break ;
			tmp = tmp->next->next;
		}
	}
	return (cpt);
}

char	*clean_token(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		q[2];

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	q[0] = 0;
	q[1] = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !q[1])
			q[0] = !q[0];
		else if (str[i] == '"' && !q[0])
			q[1] = !q[1];
		else
			res[j++] = str[i];
	}
	return (res[j] = '\0', res);
}

void	free_one_cmd(t_cmd *cmd)
{
	free_argv(cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}
