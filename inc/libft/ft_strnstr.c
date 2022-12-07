/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seba <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:06:11 by seba              #+#    #+#             */
/*   Updated: 2022/08/24 22:36:05 by seba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (i < n && big[i])
	{
		if (big[i] == little[j])
		{
			while (big[i] == little[j] && big[i] && i < n)
			{
				i++;
				j++;
			}
			if (!little[j])
				return ((char *)(big + (i - j)));
			i = i - j;
			j = 0;
		}
		i++;
	}	
	return (NULL);
}
