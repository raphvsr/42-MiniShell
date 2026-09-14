/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:46:04 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 18:48:33 by kheda            ###   ########.fr       */
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

char	*new_line(char *line, int start, int *end)
{
	char	*s;
	char	*ptr;
	int		i;
	int		j;

	ptr = ft_strchr(&line[start + 1], line[start]);
	if (!ptr)
		return (NULL);
	*end = (int)(ptr - line);
	s = malloc((ft_strlen(line) + 1) - 2);
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (i == start || i == *end)
			i++;
		else
			s[j++] = line[i++];
	}
	s[j] = 0;
	return (s);
}

char	*clean_token(t_token *token)
{
	int		i;
	int		start;
	int		end;
	char	*line;
	char	*new;

	i = 0;
	line = ft_strdup(token->value);
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			start = i;
			new = new_line(line, start, &end);
			if (!new)
				return (free(line), NULL);
			free(line);
			line = new;
			i = end - 2;
		}
		i++;
	}
	return (line);
}

void	free_one_cmd(t_cmd *cmd)
{
	free_argv(cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}
