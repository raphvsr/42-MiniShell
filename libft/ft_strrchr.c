/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:09:59 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/06 13:48:59 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	len;

	len = ft_strlen(string);
	while (len >= 0)
	{
		if (string[len] == (char)searchedChar)
			return ((char *)&string[len]);
		len--;
	}
	return (NULL);
}
