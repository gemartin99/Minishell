/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:33 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/25 12:04:02 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	nb;
	int			neg;

	nb = 0;
	neg = 1;
	while (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		++str;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg *= -1;
	while (*str >= '0' && *str <= '9')
	{
		if (((nb * 10 + (*str - 48)) < nb) && neg == 1)
			return (-1);
		else if (((nb * 10 + (*str - 48)) < nb) && neg == -1)
			return (0);
		nb = nb * 10 + (int)(*str++ - 48);
	}
	return ((int)(nb * neg));
}
