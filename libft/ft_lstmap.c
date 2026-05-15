/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:55:08 by rvasseur          #+#    #+#             */
/*   Updated: 2025/11/21 22:06:32 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;
	void	*new_cont;

	new_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_cont = f(lst->content);
		tmp = ft_lstnew(new_cont);
		if (!tmp)
		{
			del(new_cont);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}
