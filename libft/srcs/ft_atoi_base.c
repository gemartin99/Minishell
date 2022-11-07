/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:18:56 by tpou-ale          #+#    #+#             */
/*   Updated: 2021/11/11 21:05:05 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_base(const char *base)
{
	int	i;
	int	j;

	if (!base || !*base || !base[1])
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+'
			|| base[i] < 32 || base[i] > 126)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			++j;
		}
		++i;
	}
	return (i);
}

static int	ft_getnum_base(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] != c)
		++i;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	l;
	int	nb;
	int	neg;

	l = ft_check_base(base);
	if (l < 2)
		return (0);
	neg = 1;
	nb = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		++str;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg *= -1;
	while (*str && ft_strchr(base, *str) != NULL)
	{
		nb = nb * l + ft_getnum_base(*str, base);
		++str;
	}
	return (nb * neg);
}
