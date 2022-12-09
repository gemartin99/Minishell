/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:59:23 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 23:59:24 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_flag(char *str)
{
	int	i;
	
	i = 0;
	str = remove_quotes(str, 34);
	str = remove_quotes(str, 39);
	if (str[i++] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

static void	special_putstr()
{
	
}

void	ft_echo(t_cmd	**cmd)
{
	int	i;
	
	if (!(*cmd)->arg && printf("\n"))
		return ;
	i = -1;
	while ((*cmd)->arg[++i])
		printf("%s ", (*cmd)->arg[i]);
	printf("\n");
}
