/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_dolar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_dolar_echo(char *line) //funcion para checkear si hay un dolar en la linea que me mandan
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			while (line[i] != 39)
				i++;
			i++;
		}
		if (line [i] == 34)
		{
			while (line[++i] != 34)
			{
				if (line[i] == '$' && line[i + 1])
					return (1);
			}
		}
		if (line[i] == '$' && line[i + 1])
			return (1);
		i++;
	}
	return (0);
}

//cambiar valor a env's ⬇️//

int position_dolar(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			return (++i);
		i++;
	}
	return (0);
}

static int var_strcmp_echo(char *s1, char *s2) //, t_list *d) //funcion strcmp modificada para variables de entorno
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	/*if (s1[0] == '?' && !s1[1])
	{
		//printf("%d\n", d->dolar_question); hacer que si tengo $? cambiar eso por el valor de dolar_question
		//se podria hacer llamando a una funcion que cambie el valor de d->read_line cambiando el $? por el valor.
		return (0);
	}*/
	while (s2[i] && s2[i] != '=')
		i++;
	if (ft_strlen(s1) != i)
		return (1); 
	i = 0;
	while (s1[i] && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int check_special_char(char c) //funcion para checkear si despues de la variable hay algunos caracter especial ya que cambia la interpretacion de la var
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{' ||
		c == '}' || c == '[' || c == ']' || c == '!' || c == '~' ||
		c == '%' || c == '^' || c == '=' || c == '*' ||	c == '/')
		return (-1);
	return (0);
}

char *ft_name_var(char *line) //funcion que crea una variable con el nombre que tiene el argumento que me manden cn $ para luego comprarlo con las variables de entorno
{
	int j;
	int i;
	char *result;

	i = position_dolar(line);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"' && check_special_char(line[i + j]) == 0)
		j++;
	result = malloc(sizeof(char) * i + j + 1);
	if (!result)
		ft_free();
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"' && check_special_char(line[i + j]) == 0)
	{
		result[j] = line[i + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char *add_var_value_echo(char *s1) //funcion para añadir el valor de la variable de entorno a nuestra variable result
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	while (s1[i] != '=')
		i++;
	result = malloc(sizeof(char) * ft_strlen(s1) - i + 1);
	if (!result)
		ft_free();
	while(s1[++j])
		result[j - 1] = s1[i + j];
	result[j] = '\0';
	return (result);
}

char *ft_craft_result(char *line_final, char *line, char *var, int c)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (line[++i] != '$')
		line_final[i] = line[i];
	while (var[++j])
		line_final[i + j] = var[j];
	while (line[i + c])
	{
		line_final[i + j] = line[i + c];
		i++;
	}
	line_final[i + j] = '\0';
	return (line_final);
}

char *change_line_value(char *line, char *var) //funcion que cambia el valor de la linea y sustituye el $var por el valor de la variable si esa variable existe
{
	int i;
	int j;
	char *line_final;
	int c;

	i = 0;
	j = 0;
	while (line[i] != '$')
		i++;
	c = i;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != 34 && line[i + j] != 39)
		j++;
	while (line[i + j])
		i++;
	if (c == i && ft_strlen(var) < 2)
		return (NULL);
	line_final = malloc(sizeof(char) * i + ft_strlen(var));
	if (!line_final)
		ft_free();
	return (ft_craft_result(line_final, line, var, j));
}

char *ft_split_var(char *line, int i, t_list *d) //funcion que retorna el resto de una variable si hay caracteres especiales. Ej: echo "$USER@hola" esta funcion retornara @hola
{
	int j;
	char *res;

	d->control_var_reminder = 1;
	j = i;
	while (line[i])
		i++;
	res = malloc(sizeof(char) * i - j + 1);
	if (!res)
		ft_free();
	i = 0;
	while (line[j])
	{
		res[i] = line[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_strjoin_special(char *s1, char *s2, size_t i, size_t c) //funcion que concatena la $var y /aaa o lo que le manden despues de una $var siempre y cuando sea caracter especial
{
	char	*str;
	size_t 	size1;

	size1 = ft_strlen(s1);
	if (s1[size1 - 1] == 34 || s1[size1 - 1] == 39)
		size1--;
	str = (char *)malloc(sizeof(char) * (size1 + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i] && i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[c])
	{
		str[i + c] = s2[c];
		c++;
	}
	str[i + c] = '\0';
	return (str);
}

char *ft_change_var(t_list *d, char *line) //funcion para detectar y cambiar el valor a la linea y que si hay un caracter especial despues de $var se concatene. Ej: $USER/aaa 
{
	char *name_var;
	int i;
	char *result;

	i = 0;
	name_var = ft_name_var(line);
	while (line[i] && line[i] != '$')
		i++;
	while (line[++i])
		if (check_special_char(line[i]) == -1)
		{
			d->var_reminder = ft_split_var(line, i, d);
			break;
		}
	if (!name_var)
		return (NULL);
	i = -1;
	while (++i < d->num_env)
	{
		if (var_strcmp_echo(name_var, d->ent_var[i]) == 0) //, d) == 0)
		{
			free(name_var);
			result = add_var_value_echo(d->ent_var[i]);
			return (change_line_value(line, result));
		}
		else if (i + 1 == d->num_env)
			return (change_line_value(line, " "));
	}
	parsing(d->read_line, d);
	return(0);
}

static int ft_isdigit_special(int i) //funcion que checkea si es un numero o caracter especial
{
	if (i == '*' || i == '@' || i == 92)
		return (1);
	else if (i < 48 || i > 57)
		return (0);
	return (1);
}

int check_dolar_and_digit(char *s) //funcion para detectar si hay un digito despues de un dolar para posteriormente quitarlo , tanto el dolar como el numero
{
	int i;

	i = -1;
	while(s[++i] && s[i] != '$')
		;
	if (s[i] && s[i] == '$' && s[i + 1] && ft_isdigit_special(s[i + 1]) == 1)
		return (0);
	else
		return (1);
}

char *quit_dollar_and_digit(char *s) //funcion recursiva para ir quitando todos los digitos y dolares sobrantes. ej: $1aaa $2bb. Quedaria asi aaa bb
{
	char *res;
	int i;
	int j;

	i = -1;
	while(s[++i])
	{
		if (s[i] && s[i] == '$' && s[i + 1] && ft_isdigit_special(s[i + 1]) == 1)
		{
			j = -1;
			res = malloc(sizeof(char) * ft_strlen(s) - 1);
			if (!res)
				ft_free();
			while (++j < i)
				res[j] = s[j];
			i++;
			while (s[++i])
			{
				res[j] = s[i];
				j++;
			}
			res[j] = '\0';
			free(s);
			s = quit_dollar_and_digit(res);
		}
	}
	return (s);
}

//cambiar valor a env's ⬆️//

char *change_dolar_x_var(t_list *d)
{
	int i;

	i = 0;
	if (check_dolar_and_digit(d->read_line) == 0)
		d->read_line = quit_dollar_and_digit(d->read_line);
	if (check_dolar_echo(d->read_line) == 0)
		return (d->read_line);
	d->control_var_reminder = 0;
	d->read_line = ft_change_var(d, d->read_line);
	if (d->read_line == NULL)
		d->read_line = "echo";
	if (check_dolar_echo(d->read_line) == 1)
		change_dolar_x_var(d);
	d->echo_control = 1;
	if (d->control_var_reminder == 1)
		d->read_line = ft_strjoin_special(d->read_line, d->var_reminder, 0, 0);
	i = -1;
	parsing(d->read_line, d);
	return (d->read_line);
}
