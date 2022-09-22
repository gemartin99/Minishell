/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_dash_n(char *s)
{
	int i;

	i = 0;
	if (s[0] != '-')
		return (-1);
	if (s[1] != 'n')
		return (-1);
	while (s[++i])
	{
		if (s[i] == 'n')
			;
		else
			return (-1);
	}
	return (0);
}

int check_more_n(char *s, int i, int control)
{
	int j;

	j = i;
	while (s[i] == ' ')
		i++;
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		while (s[++i] == 'n')
			;
		if (s[i] != ' ')
			return (j + 1);
	}
	while (s[i] == ' ' || (s[i + 1] == ' ' && s[i] == '-'))
	{
		if (s[i] == '-' && s[i + 1] == ' ')
			return (i);
		i++;
	}
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		control = 1;
		i = check_more_n(s, i, control);
	}
	else if (s[i + 1] == '-' && s[i + 2] == 'n')
	{
		control = 1;
		i = check_more_n(s, i, control);
	}
	return (i);
}

int calc_dash_n(char *s, int i)
{
	int control;

	control = 0;
	while (s[++i])
	{
		if (s[i] == ' ')
			break;
	}
	i = check_more_n(s, i, control);
	while (s[i] == ' ')
		i--;
	return (i);
}

int ft_skip_echo(char *s, int i)
{
	while (s[i] != 'E' && s[i] != 'e')
		i++;
	while (s[i] != ' ')
		i++;
	return (i);
}

int start_arg(char *s)
{
	int i;

	i = 0;
	while (s[i] != 'o' && s[i] != 'O')
		i++;
	i++;
	while (s[i] == ' ')
		i++;
	i--;
	return (i);
}

void ft_echo_write(t_list *d, int i, int condition)
{
	i = start_arg(d->read_line);
	if (check_dash_n(d->argu[1]) == 0)
		{
			condition = 0;
			i = calc_dash_n(d->read_line, i);
			while (d->read_line[i] != ' ')
				i--;
		}
	while (d->read_line[++i])
		{
			if (d->read_line[i] == 39)
			{
				while (d->read_line[++i] != 39)
					write(1, &d->read_line[i], 1);
			}
			if (d->read_line[i] == 34)
			{
				while (d->read_line[++i] != 34)
					write(1, &d->read_line[i], 1);
			}
			if (d->read_line[i] != 34 && d->read_line[i] != 39)
				write(1, &d->read_line[i], 1);
			while (d->read_line[i] == ' ' && d->read_line[i + 1] == ' ')
				i++;
		}
		if (condition == 1)
			ft_putchar_fd('\n', 1);
		d->echo_control = 0;
}

int ft_echo(t_list *d)
{
	int i;
	int condition;

	condition = 1;
	i = 0;
	//if (d->read_line[0] != 'e' || d->read_line[0] != 'E')
	i = ft_skip_echo(d->read_line, i);
	while (d->read_line[i] != ' ')
		i++;
	if (check_dolar_echo(d->read_line) == 1 && d->echo_control == 0)
		d->read_line = change_dolar_x_var(d);
	if (d->num_args == 1 && check_echo_word(d->argu[0]) == 0)
		return (write(1, "\n", 1) - 1);
	else
		ft_echo_write(d, i, condition);
	return (0);
}
