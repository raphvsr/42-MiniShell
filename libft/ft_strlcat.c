/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:11:04 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/21 20:53:29 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_l;
	size_t	src_l;

	j = 0;
	dest_l = 0;
	src_l = ft_strlen(src);
	while (dest_l < size && dest[dest_l] != '\0')
		dest_l++;
	if (dest_l == size)
		return (size + src_l);
	i = dest_l;
	while (src[j] && i + 1 < size)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest_l + src_l);
}
