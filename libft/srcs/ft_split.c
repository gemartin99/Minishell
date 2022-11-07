/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:36 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/25 15:17:14 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_clear_split(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static char	**ft_set_strarr(char **arr, size_t i, char *str, char *s)
{
	arr[i] = ft_substr(s, 0, str - s);
	if (!arr[i])
		return (ft_clear_split(arr));
	return (arr);
}

static char	**ft_split_arr(char **arr, char *str, char c)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	while (*str)
	{
		if (*str != c && !s)
			s = str;
		else if (*str == c && s)
		{
			if (ft_set_strarr(arr, i++, str, s) == NULL)
				return (NULL);
			s = NULL;
		}
		++str;
	}
	if (s != NULL && ft_set_strarr(arr, i++, str, s) == NULL)
		return (NULL);
	arr[i] = NULL;
	return (arr);
}

static size_t	ft_strarr_len(char const *s, char c)
{
	size_t	len;

	len = (*s && (*s != c));
	while (*s)
	{
		if (*s == c)
		{
			while (*s && *s++ == c)
				if (*s && *s != c)
					++len;
		}
		else
			++s;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strarr_len(s, c);
	arr = (char **)ft_calloc(len + 1, sizeof(char *));
	if (arr == NULL)
		return (arr);
	arr = ft_split_arr(arr, (char *)s, c);
	if (arr != NULL && *arr == NULL && len)
		free(arr);
	return (arr);
}
