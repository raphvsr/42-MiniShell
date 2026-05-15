/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:09:59 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/21 20:41:51 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == src)
		return (dest);
	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (dest > src)
	{
		i = count;
		while (count-- > 0)
			d[count] = s[count];
	}
	else
	{
		while (i < count)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
