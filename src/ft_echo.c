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
#include "../inc/libft/libft.h"

static int	is_flag(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = str_noquotes(ft_strdup(str));
	if (temp[i++] != '-')
		return (0);
	while (temp[i] == 'n')
		i++;
	if (temp[i])
		return (0);
	free(temp);
	return (1);
}

static void	special_putstr(char *str, char *next)
{
	int	i;
	int	doubles;
	int	simples;
	int control;

	i = 0;
	control = 0;
	doubles = 1;
	simples = 1;
	while (str[i])
	{
		if (str[i] == ';')
		{
			control = 1;
			printf(" ");
		}
		if (str[i] != ';' && ft_isprint(str[i]))
			printf("%c", str[i]);
		i++;
	}
	if (next && control == 0)
		printf(" ");
	free(str);
}

int	ft_echo(t_cmd	**cmd)
{
	int	i;
	int	n;

	if (!(*cmd)->arg && printf("\n"))
		return (0);
	i = 0;
	n = 1;
	while ((*cmd)->arg[i] && is_flag((*cmd)->arg[i]))
	{
		n = 0;
		i++;
	}
	while ((*cmd)->arg[i])
	{
		special_putstr(str_noquotes((*cmd)->arg[i]), (*cmd)->arg[i + 1]);
		i++;
	}
	if (n)
		printf("\n");
	return (0);
}
