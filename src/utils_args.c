/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:21:33 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 02:21:37 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_args(char *s) //funcion que cuenta el numero de argumentos que me mandan
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (s[++i])
	{
		if ((s[i] != 32 && s[i] != 34 && s[i] != 39)
			&& (s[i + 1] == 32 || s[i + 1] == '\0'
				|| s[i + 1] == 34 || s[i + 1] == 39))
			res++;
		if (s[i] == 34 || s[i] == 39)
		{
			res++;
			i = get_next_quote(i + 1, s, s[i]);
		}
	}
	return (res);
}

int	get_next_quote(int i, char *str, char c) //Devuelve la posicion de la siguiente quote
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_check_dquote_pair(char *s, int *i, char c)
{
	int	n;

	n = 1;
	while (s[*i + 1] && s[*i + 1] != c)
		(*i)++;
	if (s[*i + 1] == c)
		n++;
	(*i)++;
	return (n);
}

int	ft_check_dquote(char *s, int simple, int doble, t_msh *msh)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
			doble += ft_check_dquote_pair(s, &i, s[i]);
		if (s[i] == 39)
			simple += ft_check_dquote_pair(s, &i, s[i]);
		if (doble % 2 != 0 || simple % 2 != 0)
		{
			msh->flags->quote = 1;
			printf("dquote>\n");
			return (0);
		}
	}
	return (1);
}

int		start_line(t_msh **msh, char *read_line, char ***lines)
{
	(*msh)->flags->quote = ft_check_dquote(read_line, 2, 2, (*msh));
	if ((*msh)->flags->quote == 0)
		return (1);
	(*msh)->flags->pipe = ft_count_pipes(read_line);
	if ((*msh)->flags->pipe == -1)
		return (1);
	*lines = ft_split_pipes(read_line);
	if (!(*lines))
		return (1);
	return (0);
}