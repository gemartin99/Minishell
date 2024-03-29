/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:31 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:25:33 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*actual_path(int i)
{
	char	*s;
	char	*res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		exit_error("Error malloc", 22);
	if (!getcwd(s, MAXPATHLEN))
		exit_error("Error malloc", 22);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		exit_error("Error malloc", 23);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[i] = '\0';
	return (res);
}

//funcion para saber mi ruta actual
int	ft_pwd(int i)
{
	char	*s;
	char	*res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		exit_error("Error malloc", 22);
	if (!getcwd(s, MAXPATHLEN))
		return (10);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		exit_error("Error malloc", 23);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[i] = '\n';
	if (write(1, &res[0], i + 1) != i + 1)
		return (-1);
	return (0);
}
