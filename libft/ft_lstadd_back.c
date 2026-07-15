/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:04:55 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/20 21:00:05 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newl)
{
	t_list	*tmp_list;

	if (!lst || !newl)
		return ;
	if (*lst == NULL)
	{
		*lst = newl;
		return ;
	}
	tmp_list = *lst;
	while (tmp_list->next != NULL)
		tmp_list = tmp_list->next;
	tmp_list->next = newl;
}
