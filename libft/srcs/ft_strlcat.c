/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:36 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 11:19:27 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = -1;
	while (src[++j] && j + i < dstsize - 1 && dstsize > 0)
		dst[i + j] = src[j];
	dst[i + j] = 0;
	if (dstsize < i + j)
		return (dstsize + ft_strlen(src));
	return (i + ft_strlen(src));
}
