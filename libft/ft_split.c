/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:44:08 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/21 22:00:08 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *tosplit, char sep)
{
	int	count;

	count = 0;
	while (*tosplit)
	{
		if (*tosplit != sep)
		{
			count++;
			while (*tosplit && *tosplit != sep)
				tosplit++;
		}
		while (*tosplit && *tosplit == sep)
			tosplit++;
	}
	return (count);
}

char	*mal_words(char *s, char c)
{
	int		lgt;
	char	*str;
	int		i;

	i = 0;
	lgt = 0;
	while (s[lgt] && s[lgt] != c)
		lgt++;
	str = malloc(lgt + 1);
	if (!str)
		return (NULL);
	while (i < lgt)
	{
		str[i] = s[i];
		i++;
	}
	str[lgt] = '\0';
	return (str);
}

void	free_all(char **arr, int n)
{
	while (n >= 0)
	{
		free(arr[n]);
		n--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			str[i] = mal_words((char *)s, c);
			if (!str[i])
				return (free_all(str, i - 1), NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	str[i] = 0;
	return (str);
}
