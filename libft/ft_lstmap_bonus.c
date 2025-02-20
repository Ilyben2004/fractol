/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:35:48 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/07 18:34:43 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*newnode;
	void	*content;

	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		newnode = NULL;
		content = f(lst->content);
		if (content)
			newnode = ft_lstnew(content);
		if (!newnode)
		{
			if (content)
				del(content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, newnode);
		lst = lst->next;
	}
	return (head);
}
