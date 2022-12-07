/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seba <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:01:55 by seba              #+#    #+#             */
/*   Updated: 2022/08/16 14:49:33 by seba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total;

	total = nmemb * size;
	res = malloc (total);
	if (!res)
		return (NULL);
	ft_bzero(res, total);
	return (res);
}
