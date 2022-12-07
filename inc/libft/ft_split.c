/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seba <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:04:20 by seba              #+#    #+#             */
/*   Updated: 2022/10/28 11:39:01 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	n_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	j = 0;
	if (ft_strlen(s) == 0)
		return (1);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j + 1);
}

static size_t	n_letters(char const *s, size_t j, char c)
{
	size_t	i;
	size_t	m;

	m = j;
	while (s[j] != c && s[j])
		j++;
	i = j - m;
	return (i);
}

static char	**ft_free(int i, char **str)
{
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return (NULL);
}

static char	**ft_fill(char **str, const char *s, size_t wrds, char c)
{
	size_t	i;
	size_t	t;
	size_t	l;

	t = 0;
	while (s[t] && s[t] == c)
		t++;
	i = 0;
	l = 0;
	while (i < wrds - 1)
	{
		t = t + l;
		l = n_letters(s, t, c);
		str[i] = ft_substr(s, t, l);
		if (!str[i])
			return (ft_free((int)i, str));
		while (s[t + l] == c)
			t++;
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	wrds;

	wrds = n_words(s, c);
	str = ft_calloc(wrds, sizeof(char *));
	if (!str)
		return (NULL);
	return (ft_fill(str, s, wrds, c));
}
