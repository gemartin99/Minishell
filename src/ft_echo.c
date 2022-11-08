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
#include "../inc/minishell.h"

int check_dash_n(const char *s) // funcion que checkea si hay un argumento -n despues de echo
{
	int i;

	i = 0;
	if (s[0] && s[0] != '-')
		return (-1);
	if (s[1] && s[1] != 'n')
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

int check_more_n(char *s, int i) //funcion que checkea si hay mas -n o no quedan mas
{
	int j;

	j = i;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] && s[i] == '-' && s[i + 1] == 'n')
	{
		while (s[++i] && s[i] == 'n')
			;
		if (s[i] && s[i] != ' ')
			return (j + 1);
	}
	while (s[i] && (s[i] == ' ' || (s[i + 1] == ' ' && s[i] == '-')))
	{
		if (s[i] == '-' && s[i + 1] == ' ')
			return (i);
		i++;
	}
	if ((s[i] && s[i + 1] && s[i] == '-' && s[i + 1] == 'n') || (s[i + 1] && s[i + 2] && s[i + 1] == '-' && s[i + 2] == 'n'))
		i = check_more_n(s, i);
	return (i);
}

int calc_dash_n(char *s, int i) //funcion para ubicar el indice justo despues del ultimo arg -n
{
	while (s[++i])
	{
		if (s[i] && s[i] == ' ')
			break;
	}
	i = check_more_n(s, i);
	return (i);
}

int ft_skip_echo(char *s, int i) //funcion paara ubicarme cuando empieza el comando echo por si hay espacios antes
{
	while (s[i] && s[i] != 'E' && s[i] != 'e')
		i++;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

int start_arg(const char *s) //funcion que me ubica al final del comando echo y por ende despues al principio del arguemnto
{
	int i;

	i = 0;
	while (s[i] && s[i] != 'o' && s[i] != 'O')
		i++;
	i++;
	while (s[i] && s[i] == ' ')
		i++;
	i--;
	return (i);
}

/*
void write_conditions(t_msh *d, int i)
{
	if (d->read_line[i] == ';')
	{
		write(1, " ", 1);
		i++;
	}
	else if (d->read_line[i] == 39)
	{
		while (d->read_line[++i] != 39)
			write(1, &d->read_line[i], 1);
	}
	else if (d->read_line[i] == 34)
	{
		while (d->read_line[++i] != 34)
			write(1, &d->read_line[i], 1);
	}
	else if (d->read_line[i] != 34 && d->read_line[i] != 39)
		write(1, &d->read_line[i], 1);
}
*/

void ft_write_path(int i, char *s)
{
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			write(1, &s[i], 1);
	}
}

int check_exist_more_arg(char *s, int i) //funcion para checkear que no venga solo -n y no haya nada que printar
{
	int j;

	j = i;
	while (s[i] && s[i] == ' ')
		i++;
	if (i == ft_strlen(s))
		return (i);
	return (j);
}

void ft_echo_write(t_msh *d, int i, int condition)
{
	i = start_arg(d->read_line);
	if (check_dash_n(d->argu[1]) == 0)
	{
		condition = 0;
		i = calc_dash_n(d->read_line, i);
		i = check_exist_more_arg(d->read_line, i);
		if (i != ft_strlen(d->read_line))
			while (d->read_line[i] && d->read_line[i] != ' ')
				i--;
	}
	while (d->read_line[++i])
	{
		if (d->read_line[i] == '~' && d->read_line[i - 1] == ' ' && (d->read_line[i + 1] == ' ' || d->read_line[i + 1] == '\0' || d->read_line[i + 1] == '/'))
			write(1, "/Users/gemartin", 15); //cambiar la linea por valor $HOME y si no existe esa var pues nidea;
		else if (d->read_line[i] == ';')
		{
			write(1, " ", 1);
			i++;
		}
		else if (d->read_line[i] && d->read_line[i] == 39)
		{
			while (d->read_line[++i] && d->read_line[i] != 39)
			{
				if (d->read_line[i] == 28)
					ft_putchar_fd('"', 1);
				else
					write(1, &d->read_line[i], 1);
			}
		}
		else if (d->read_line[i] && d->read_line[i] == 34)
		{
			while (d->read_line[++i] && d->read_line[i] != 34)
			{
				if (d->read_line[i] == 29)
					write(1, "'", 1);
				else
					write(1, &d->read_line[i], 1);
			}
		}
		else if (d->read_line[i] && d->read_line[i] != 34 && d->read_line[i] != 39)
			write(1, &d->read_line[i], 1);
		while (d->read_line[i] && d->read_line[i + 1] && d->read_line[i] == ' ' && d->read_line[i + 1] == ' ')
			i++;
	}
	if (condition == 1)
		ft_putchar_fd('\n', 1);
	d->echo_control = 0;
}

char *ft_quit_quotes(char *s) //funcion para quitar comillas en caso de que esten asi: 'echo'
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 4;
	res = malloc(sizeof(char) * ft_strlen(s) - 1);
	if (!res)
		ft_free();
	res[0] = 'e';
	res[1] = 'c';
	res[2] = 'h';
	res[3] = 'o';
	while (s[i] && s[i] != ' ')
		i++;
	while (s[i])
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

int ft_echo(t_msh *d)
{
	int i;
	int condition;

	condition = 1;
	i = 0;
	if (check_dolar_echo(d->read_line) == 1 && d->echo_control == 0)
		d->read_line = change_dolar_x_var(d);
	if (d->read_line[0] == 34 || d->read_line[0] == 39)
	{
		d->read_line = ft_quit_quotes(d->read_line);
		ft_echo(d);
	}
	else if (d->num_args == 1 && check_echo_word(d->argu[0]) == 0)
		return ((int)(write(1, "\n", 1) - 1));
	else
	{
		i = ft_skip_echo(d->read_line, i);
		while (d->read_line[i] && d->read_line[i] != ' ')
			i++;
		ft_echo_write(d, i, condition);
	}
	return (0);
}