/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:33 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 11:44:24 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoi_u(const char *str)
{
	unsigned int	nb;

	nb = 0;
	while (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		if (nb * 10 + (*str - '0') > nb)
		{
			nb *= 10;
			nb += *str++ - '0';
		}
		else
			return (0);
	}
	if (*str)
		return (0);
	return (nb);
}
