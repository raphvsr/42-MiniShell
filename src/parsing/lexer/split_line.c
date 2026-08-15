/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 01:36:20 by kheda             #+#    #+#             */
/*   Updated: 2026/08/15 11:39:33 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include <stdio.h>
static int	free_all(char **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	cpt;
	int	flag = 6;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			cpt++;
		else if (s[i] == c && (s[i + 1] == '\'' || s[i + 1] == '"'))
			flag = 1;
		while (flag == 1 && s[i])
		{
			if ((s[i] == '\'' || s[i] == '"') && s[i + 1] == c)
			{
				flag = 0;
				cpt++;
			}
			else
				i++;
		}
		i++;
	}
	return (cpt);
}

static char	*word(char const *s, int start, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	fill(char **tab, char const *s, char c)
{
	int	i;
	int	start;
	int	index;
	int	flag = 6;

	i = 0;
	index = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if ((s[i] == '\'' || s[i] == '"') || (s[i + 1] == '\'' || s[i + 1] == '"'))
			flag = 1;
		start = i;
		while (s[i])
		{
			if (flag == 1 && (s[i] == '\'' || s[i] == '"') && s[i + 1] == c)
			{
				flag = 0;
				i++;
				break;
			}
			else if (s[i] == c && flag != 1)
				break;
			i++;
		}
		if (i > start)
		{
			tab[index] = word(s, start, i - start);
			if (tab[index] == NULL)
				return (free_all(tab, index));
			index++;
		}
	}
	return (1);
}

char	**split_line(char const *s, char c)
{
	int		len;
	char	**tab;

	if (s == NULL)
		return (NULL);
	len = count_words(s, c);
	tab = malloc(sizeof(char *) * (len + 1));
	if (tab == NULL)
		return (NULL);
	tab[len] = NULL;
	if (fill(tab, s, c) == 0)
		return (NULL);
	return (tab);
}

// int main()
// {
//     char **tab = split_line("  no 'Un po' em pr", ' ');
//     for (int i = 0; i < 6; i++)
//     {
//         printf("%s\n", tab[i]);
//     }
// 	return (0);
// }