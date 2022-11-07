/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:17:33 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/24 11:18:24 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		nb;
	size_t	len;
	char	*str;

	len = 0;
	nb = n;
	while (nb)
	{
		nb /= 10;
		++len;
	}
	len += (n <= 0);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (str);
	str[0] = (char)((n < 0) * 45 + !n * 48);
	str[len--] = 0;
	while (n)
	{
		str[len--] = (char)(ft_abs(n % 10) + 48);
		n /= 10;
	}
	return (str);
}
