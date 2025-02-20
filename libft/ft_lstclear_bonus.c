/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:34:46 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:36:17 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*todel;
	t_list	*temp;

	if (!lst || !del)
		return ;
	if (!*lst)
		return ;
	todel = *lst;
	temp = (*lst)->next;
	while (todel)
	{
		del(todel->content);
		free(todel);
		if (temp)
		{
			todel = temp;
			temp = temp->next;
		}
		else
			todel = NULL;
	}
	*lst = NULL;
}
