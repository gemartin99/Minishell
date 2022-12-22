/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:55:09 by smiro             #+#    #+#             */
/*   Updated: 2022/12/12 12:55:13 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//funcion para contar todas las variables de entorno que no sean nulas.
int	ft_count_env(char **arg, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i + j < len)
	{
		if (arg[i + j])
			i++;
		else
			j++;
	}
	return (i - j);
}
