/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:59:32 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/20 20:55:35 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t				i;
	const unsigned char	*p1_b;
	const unsigned char	*p2_b;

	i = 0;
	p1_b = (const unsigned char *)pointer1;
	p2_b = (const unsigned char *)pointer2;
	while (i < size)
	{
		if (p1_b[i] != p2_b[i])
			return (p1_b[i] - p2_b[i]);
		i++;
	}
	return (0);
}
