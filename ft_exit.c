/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int ft_validate_num(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_list *d)
{
	int n;

	if (d->num_args > 2)
	{
		printf("exit\nbash: exit: too many arguments\n");
		return ;
	}
	else if (d->num_args == 1)
		exit (1);
	if (ft_validate_num(d->argu[1]) == 1)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", d->argu[1]);
		exit (255);
	}
	n = ft_atoi(d->argu[1]);

}