/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:09:59 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/21 20:36:19 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if ((unsigned char)string[i] == (unsigned char)searchedChar)
			return ((char *)&string[i]);
		i++;
	}
	if ((unsigned char)searchedChar == '\0')
		return ((char *)&string[i]);
	return (NULL);
}
