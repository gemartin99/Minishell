/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:37 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/25 10:53:44 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	if (start < 0 || start > ft_strlen(s))
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (s_len - start < len)
		len = s_len - start;
	substr = (char *)malloc(len * (s_len && s_len > start) + 1);
	if (substr == NULL)
		return (substr);
	ft_strlcpy(substr, s + start, len * (s_len && s_len > start) + 1);
	return (substr);
}
