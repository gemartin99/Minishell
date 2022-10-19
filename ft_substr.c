/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:12:08 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 16:12:09 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		res = malloc(1);
		if (!res)
			ft_free();
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		ft_free();
	while (start < ft_strlen(s) && i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
