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
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup(str);
	temp = remove_quotes(temp, 34);
	temp = remove_quotes(temp, 39);
	if (str[i++] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	free(temp);
	return (1);
}

static void	special_putstr(char *str, char *next)
{
	int	i;
	int	doubles;
	int	simples;

	i = 0;
	doubles = 1;
	simples = 1;
	if (str[i] == 34 || str[i] == 39)
	{
		str = remove_quotes(str, str[i]);
		doubles = -1;
		simples = -1;
	}
	while (str[i])
	{
		if (str[i] == 34 && simples != -1 && i++)
				doubles *= -1;
		if (str[i] == 39 && doubles != -1 && i++)
			simples *= -1;
		if (str[i] == ';' && next && i++)
			printf(" ");
		if (str[i] != ';' && ft_isprint(str[i]))
			printf("%c", str[i]);
		i++;
	}
	if (next)
		printf(" ");
}

void	ft_echo(t_cmd	**cmd)
{
	int	i;
	int	n;

	if (!(*cmd)->arg && printf("\n"))
		return ;
	i = 0;
	n = 1;
	while ((*cmd)->arg[i] && is_flag((*cmd)->arg[i]))
	{
		n = 0;
		i++;
	}
	while ((*cmd)->arg[i])
	{
		special_putstr((*cmd)->arg[i], (*cmd)->arg[i + 1]);
		i++;
	}
	if (n)
		printf("\n");
}
