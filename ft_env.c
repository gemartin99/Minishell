/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_env_word(char *s)
{
	if (s[0] != 'E' && s[0] != 'e')
		return (-1);
	if (s[1] != 'N' && s[1] != 'n')
		return (-1);
	if (s[2] != 'V' && s[2] != 'v')
		return (-1);
	if (s[3])
		return (-1);
	return (0);
}

int	ft_env(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->num_env)
	{
		if (d->ent_var[i] != NULL)
			printf("%s\n", d->ent_var[i]);
		i++;
	}
	return (0);
}
