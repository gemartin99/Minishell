/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:36:55 by gemartin          #+#    #+#             */
/*   Updated: 2022/06/17 13:45:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <limits.h>
#include "minishell.h"

int	static	ft_spaces(char c)
{
	return (
		c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r'
	);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				valorfinal;
	long long int	nbr;

	nbr = 0;
	i = 0;
	valorfinal = 1;
	while (str[i] && ft_spaces(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			valorfinal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < -INT_MIN && valorfinal == -1)
			return (0);
		if (nbr > INT_MAX && valorfinal == 1)
			return (-1);
	}
	return (nbr * valorfinal);
}