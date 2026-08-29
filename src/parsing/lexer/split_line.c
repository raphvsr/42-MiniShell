/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 01:36:20 by kheda             #+#    #+#             */
/*   Updated: 2026/08/27 18:46:22 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	create_token(char *s, char quote, int type) // le type WORD etc 
// {
// 	t_token *token;
// 	// int	i;
// 
// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return;
// 	// i = 0;
// 	// while (s[i])
// 	token->value = s; // adresse de la chaine donc on aura tout a partir de cette adresse ?
// 	token->type = type;   // probleme ? il faut un len d'arret, et pas toute la chaine
// 	if (quote == '\'')
// 		token->quoted = 1;
// 	else if (quote == '"')
// 		token->quoted = 2;
// 	else
// 		token->quoted = 0;
// 										// token->quoted = quoted_type_number; ??
// 	// token = token->next; // ? here
// }

static int	count_words(char const *s, char c)
{
	int	i;
	char quote;
	int	cpt;
	
	i = 0;
	cpt = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break;
		else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			if (s[i] == s[i + 1] && s[i + 1] != '|')
				i = i + 2;
			else
				i++;
		}
		else
		{
			while (s[i] && !sym(s[i]))
			{
				if (s[i] == '\'' || s[i] == '"')
				{
					quote = s[i];
					i++;
					while (s[i] != quote && s[i] != '\0')
						i++;
					if (s[i] == '\0')
						return (5); // 0
					// create_token(&s, quote, 1); // 1 -> type WORD en vrai
					quote = 0;
					i++;
				}
				else
					i++;
				// create_token(&s, 'a', 1); // 1 -> type WORD en vrai, a -> simplier, but can do any alphabetic character
			}
		}
		cpt++;
	}
	printf("%d\n", cpt);
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
	int	flag;

	i = 0;
	index = 0;
	flag = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if ((s[i] == '\'' || s[i] == '"')) //|| (s[i + 1] == '\'' || s[i + 1] == '"')
			flag = 1;
		start = i;
		while (s[i])
		{
			if ((s[i] == '\'' || s[i] == '"'))
				flag = 1;
			if (flag == 1 && (s[i + 1] == '\'' || s[i + 1] == '"')) // && s[i + 1] == c
			{
				flag = 0;
				i = i + 2;
				break;
			}
			else if (s[i] == c && flag == 0) // && !sym(s[i])
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