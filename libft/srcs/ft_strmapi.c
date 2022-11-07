/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:37 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 11:47:50 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	len = ft_strlen(s);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (str);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, s[i]);
		++i;
	}
	str[i] = 0;
	return (str);
}
