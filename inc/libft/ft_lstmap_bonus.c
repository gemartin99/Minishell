/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seba <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:27:39 by seba              #+#    #+#             */
/*   Updated: 2022/10/27 21:17:47 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*temp;
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (lst)
	{
		temp = (*f)(lst->content);
		new = ft_lstnew(temp);
		if (!new)
		{
			ft_lstclear(&head, (*del));
			del(temp);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
