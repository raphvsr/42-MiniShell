/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:37:22 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/20 21:02:51 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_list;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp_list = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp_list;
	}
	*lst = NULL;
}
