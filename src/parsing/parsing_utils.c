/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:46:04 by kheda             #+#    #+#             */
/*   Updated: 2026/09/11 02:46:05 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

int	sym(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>');
}

int	count_word_token(t_token *tmp)
{
	int	cpt;

	cpt = 0;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

char	*new_line(char *line, int start, int end)
{
	char	*s;
	int		i;
	int		j;

	s = malloc((strlen(line) + 1) - 2);
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == line[start] || line[i] == line[end])
			i++;
		else
		{
			s[j] = line[i];
			i++;
			j++;
		}
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
	start = 0; // no need ?
	line = ft_strdup(token->value);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			start = i;
			end = (int)(ft_strchr(&line[start + 1], line[start]) - line);
			new = new_line(line, start, end);
			if (!new)
				return (free(line), NULL); // FREE LINE HERE ???? MESSAGE ????
			free(line);
			line = new;
			i = end - 2;
		}
		i++;
	}
	return (line);
}
