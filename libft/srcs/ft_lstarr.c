/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_lst_strarr_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:33 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 12:15:56 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_lst_strarr(char **arr)
{
	t_list	*head;
	t_list	*temp;

	if (*arr == NULL)
		return (NULL);
	head = NULL;
	while (*arr)
	{
		temp = ft_lstnew(*arr++);
		if (!temp)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, temp);
	}
	return (head);
}
