/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_element_i_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:33 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 12:16:01 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_element_i(t_list *lst, size_t i)
{
	size_t	j;

	j = 0;
	while (lst != NULL)
	{
		if (j++ == i)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
