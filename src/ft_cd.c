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
#include "../inc/minishell.h"

int check_dolar_cd(char *line) //funcion para checkear si hay un dolar en la linea que me mandan
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			i++;
		}
		if (line [i] == 34)
		{
			while (line[++i] && line[i] != 34)
			{
				if (line[i] == '$' && line[i + 1])
					return (1);
			}
		}
		if (line[i] && line[i] == '$' && line[i + 1])
			return (1);
		i++;
	}
	return (0);
}


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

int	ft_cd(t_msh *d)
{
	char	*path;
	int		i;

	i = 0;
	//hacer que variable entorno $OLDPWD tenga el valor de la ruta actual 
	//antes de hacer algun CD siempre y cuando el CD no sea hacia $OLDPWD
	if (d->argu[1] && check_dolar_cd(d->argu[1]) == 1)
		d->read_line = change_dolar_x_var(d);
	path = get_path(i);
	if (d->num_args == 1)
		chdir(getenv("HOME"));
	if (d->num_args != 1)
	{
		if (chdir(d->argu[1]) == -1)
			printf("bash: cd: %s: No such file or directory\n", d->argu[1]);
	}
	return (0);
}