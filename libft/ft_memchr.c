/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:16:40 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/21 17:56:04 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	size_t			i;
	unsigned char	*ptr_b;

	i = 0;
	ptr_b = (unsigned char *)ptr;
	while (i < count)
	{
		if (ptr_b[i] == (unsigned char)ch)
			return ((void *)&ptr_b[i]);
		i++;
	}
	return (NULL);
}
