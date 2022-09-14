/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:46:36 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 16:46:44 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int count_args(char *s)
{
	int i;
	int res;

	i = -1;
	res = 0;
	if (!s)
		return (res);
	while (s[++i])
	{
		if ((s[i] != 32 && s[i] != 34 && s[i] != 39) && (s[i + 1] == 32 || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
			res++;
		if (s[i] == 34)
		{
			res++;
			while (s[++i] != 34)
				;
		}
		if (s[i] == 39)
		{
			res++;
			while (s[++i] != 39)
				;
			i++;
		}
	}
	return (res);
}

void ft_free_arg(t_list *d)  //funcion por si falla una reserva de memoria de substr
{
	int i;

	i = -1;
	while (d->argu[++i])
		free(d->argu[i]);
	free(d->argu);
}

int choose_arg(char *s, t_list *d)
{
	int pos;
	int i;
	int start;

	d->num_args = count_args(s);
	d->argu = malloc(sizeof(char *) * (d->num_args));
	if (d->argu == NULL)
		return (-1);
	i = -1;
	start = 0;
	pos = 0;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			start = i + 1;
			while (s[++i] != 34)
				;
			d->argu[pos] = ft_substr(s, start, i - start);
			if (d->argu[pos] == NULL)
			{
				ft_free_arg(d);
				return (-1);
			}
			pos++;
		}
		if (s[i] == 39)
		{
			start = i + 1;
			while (s[++i] != 39)
				;
			d->argu[pos] = ft_substr(s, start, i - start);
			if (d->argu[pos] == NULL)
			{
				ft_free_arg(d);
				return (-1);
			}
			pos++;
		}
		if ((s[i] == ' ' || s[i] == 34 || s[i] == 39) && s[i + 1] != ' ')
			start = i + 1;
		if ((s[i] != ' ' && s[i] != 34 && s[i] != 39) && (s[i + 1] == ' ' || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
		{
			d->argu[pos] = ft_substr(s, start, i - start + 1);
			if (d->argu[pos] == NULL)
			{
				ft_free_arg(d);
				return (-1);
			}
			pos++;
		}
	}
	return (0);
}

int parsing(char *s, t_list *d)
{
	int i;
	int simple = 0;
	int doble = 0;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			doble++;
			while (s[i + 1] && s[i + 1] != 34)
				i++;
			if (s[i + 1] == 34)
				doble++;
			i++;
		}
		if (s[i] == 39)
		{
			simple++;
			while (s[i + 1] && s[i + 1] != 39)
				i++;
			if (s[i + 1] == 39)
				simple++;
			i++;
		}
	}
	if (doble % 2 != 0 || simple % 2 != 0)
	{
		d->quotes = 1;
		printf("dquote>\n");
		return (0);
	}
	if (choose_arg(s, d) == -1)
		return (-1);
	return (0);
}
