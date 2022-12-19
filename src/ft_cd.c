/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:44 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:25:45 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_cmd **cmd)
{
	int		i;

	i = 0;
	//hacer que variable entorno $OLDPWD tenga el valor de la ruta actual 
	//antes de hacer algun CD siempre y cuando el CD no sea hacia $OLDPWD
	if ((*cmd)->num_arg == 0)
		chdir(getenv("HOME"));
	else
	{
		if (chdir((*cmd)->arg[0]) == -1)
			printf("bash: cd: %s: No such file or directory\n", (*cmd)->arg[0]);
	}
	return (0);
}
