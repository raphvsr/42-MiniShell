/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:06:42 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/17 16:48:56 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_lgt;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	total_lgt = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * total_lgt + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, total_lgt + 1);
	ft_strlcat(str, s2, total_lgt + 1);
	str[total_lgt] = '\0';
	return (str);
}
