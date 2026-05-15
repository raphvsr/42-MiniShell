/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:10:48 by marvin            #+#    #+#             */
/*   Updated: 2025/11/20 20:55:48 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t size)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)ptr;
	while (i < size)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
