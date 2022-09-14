/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_pwd(int i)
{
	char	*s;
	char	*res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		ft_free();
	getcwd(s, MAXPATHLEN);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		ft_free();
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[i] = '\n';
	if (write(1, &res[0], i + 1) != i + 1)
		return (-1);
	return (0);
}
