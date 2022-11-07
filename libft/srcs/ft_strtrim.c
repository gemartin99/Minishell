/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:37 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 11:46:14 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_set(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*trimmed;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	while (ft_char_in_set(*s1++, set))
		--len;
	if (!len)
		return (ft_strdup(""));
	--s1;
	while (ft_char_in_set(s1[len - 1], set))
		--len;
	trimmed = (char *)malloc(len + 1);
	if (trimmed == NULL)
		return (trimmed);
	ft_strlcpy(trimmed, s1, len + 1);
	return (trimmed);
}
