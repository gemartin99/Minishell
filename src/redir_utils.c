/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:25:27 by smiro             #+#    #+#             */
/*   Updated: 2022/12/14 13:25:29 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	isdifoperator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	redir_type(char *str)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = get_next_quote(i + 1, str, str[i]);
		if (str[i] == '>' && str[i + 1] != '>'
			&& !isdifoperator(str[i + 1]) && !error)
			return (1);
		if (str[i] == '>' && str[i + 1] == '>'
			&& !isdifoperator(str[i + 2]) && !error)
			return (2);
		if (str[i] == '<' && str[i + 1] != '<'
			&& !isdifoperator(str[i + 1]) && !error)
			return (3);
		if (str[i] == '<' && str[i + 1] == '<'
			&& !isdifoperator(str[i + 2]) && !error)
			return (4);
		if (isdifoperator(str[i]))
			error = -1;
	}
	return (error);
}

int	is_redir(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (redir_type(arg[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	operator_char(int n)
{
	if (n == 1 || n == 2)
		return ('>');
	else if (n == 3 || n == 4)
		return ('<');
	return (0);
}

int	get_next_diff(int i, char *str)
{
	while (str[i] && !isdifoperator(str[i]))
		i++;
	return (i);
}
