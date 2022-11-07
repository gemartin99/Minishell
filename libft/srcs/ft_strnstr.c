/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:37 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/25 11:03:37 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;

	h = (char *)haystack;
	if (!*needle)
		return (h);
	while (*h && len--)
	{
		if (*h == *needle && ft_strlen(needle) <= len + 1
			&& !ft_strncmp(h, needle, ft_strlen(needle)))
			return (h);
		else
			++h;
	}
	return (NULL);
}
