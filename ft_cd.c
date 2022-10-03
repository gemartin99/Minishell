/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_path(int i)
{
	char	*s;
	char	*res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	getcwd(s, MAXPATHLEN);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
	{
		free(s);
		ft_free();
	}
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[++i] = '\0';
	return (res);
}

int	ft_cd(t_list *d)
{
	char	*path;
	int		i;

	i = 0;
	//hacer que variable entorno $OLDPWD tenga el valor de la ruta actual 
	//antes de hacer algun CD siempre y cuando el CD no sea hacia $OLDPWD
	path = get_path(i);
	if (d->num_args == 1)
		chdir(getenv("HOME"));
	if (d->num_args == 2)
	{
		if (chdir(d->argu[1]) == -1)
			printf("bash: cd: %s: No such file or directory\n", d->argu[1]);
	}
	return (0);
}
