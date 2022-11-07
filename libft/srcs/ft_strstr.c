/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:37 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 11:20:12 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*h;

	h = (char *)haystack;
	if (!*needle)
		return (h);
	while (*h)
	{
		if (*h == *needle && !ft_strncmp(h, needle, ft_strlen(needle)))
			return (h);
		else
			++h;
	}
	return (NULL);
}
