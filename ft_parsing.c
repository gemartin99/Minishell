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

int count_args(char *s) //funcion que cuenta el numero de argumentos que me mandan
{
	int i;
	int res;

	i = -1;
	res = 0;
	if (!s)
		return (res);
	while (s[++i])
	{
		if (s[i] && (s[i] != 32 && s[i] != 34 && s[i] != 39) && (s[i + 1] == 32 || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
			res++;
		if (s[i] == 34)
		{
			res++;
			while (s[i] && s[++i] != 34)
				;
		}
		if (s[i] == 39)
		{
			res++;
			while (s[i] && s[++i] != 39)
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

void ft_free_args(t_list *d) //funcion que libera toda la memoria de d->argu en el caso de que exista
{
	int i;

	i = -1;
	if (d->argu)
	{
		while (i < d->num_env && d->argu[++i])
			free(d->argu[i]);
		free(d->argu);
	}
}

int choose_arg(char *s, t_list *d) //funcion para guardar lo que me mandan en var args
{
	int pos;
	int i;
	int start;

	d->num_args = count_args(s);
	ft_free_args(d);
	d->argu = malloc(sizeof(char *) * (d->num_args) + 1);
	if (d->argu == NULL)
		ft_free();
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
				ft_free();
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
				ft_free();
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
				ft_free();
			}
			pos++;
		}
	}
	d->argu[pos] = NULL;
	return (0);
}

char *quit_null(char *s, int i) //funcion para quitar argumentos nulos sin espacios antes y despues
{
	 int j;
	 char *res;

	 s[i] = 48;
	 s[i + 1] = 48;
	 j = -1;
	 res = malloc(sizeof(char) * ft_strlen(s)) - 1;
	 if (!res)
	 	ft_free();
	 while (++j < i)
	 	res[j] = s[j];
	 while (s[j + 2])
	 {
	 	res[j] = s[j + 2];
	 	j++;
	 }
	 res[j] = '\0';
	 if (s)
	 	s = NULL;
	 return (res);
}

char *quit_null_space(char *s, int i) //funcion para quitar argumentos nulos si hay espacios antes y despues del argumento
{
	 int j;
	 char *res;

	 s[i] = 48;
	 s[i + 1] = ';';
	 j = -1;
	 res = malloc(sizeof(char) * ft_strlen(s));
	 if (!res)
	 	ft_free();
	 while (++j < i)
	 	res[j] = s[j];
	 while (s[j + 1])
	 {
	 	res[j] = s[j + 1];
	 	j++;
	 }
	 res[j] = '\0';
	 if (s)
	 	s = NULL;
	 return (res);
}

char *change_null_args(char *s, t_list *d)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 && s[i + 1] != 34)
			while (s[++i] != 34)
				;
		else if (s[i] == 39 && s[i + 1] != 39)
			while (s[++i] != 39)
				;	
		else if (s[i] == ' ' && (s[i + 1] == 34 || s[i + 1] == 39) && (s[i + 2] == 34 || s[i + 2] == 39) && s[i + 3] == ' ')
		{
			i++;
			s = quit_null_space(s, i);
			d->num_args--;
			s = change_null_args(s, d);
		}
		else if ((s[i] == 34 && s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
		{
			s = quit_null(s, i);
			d->num_args--;
			s = change_null_args(s, d);
		}
	}
	return (s);
}

//funciones comentadas que intentan arreglar el fallo cuando: echo -n" "hola 

/*char *quit_quotes(char *s, int i) //funcion para eliminar las comillas en argumentos con solo espacio
{
	int j;
	char *res;


	j = -1;
	res = malloc(sizeof(char) * ft_strlen(s) - 1);
	if (!res)
		ft_free();
	while (s[++j] && j < i)
		res[j] = s[j];
	res[j] = s[++i];
	while(s[++i])
	{
		res[++j] = s[i]; 
	}
	res[j] = '\0';
	free(s);
	return (res);
}

char *quit_null_space(char *s) //funcion para detectar si hay que quitar las comillas en argumentos con solo un espacio ej: ' '
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 && s[i + 1] == ' ' && s[i + 2] == 34)
		{
			s = quit_quotes(s, i);
			d->num_args--;
		}
		else if (s[i] == 39 && s[i + 1] == ' ' && s[i + 2] == 39)
		{
			s = quit_quotes(s, i);
			d->num_args--;
		}
	}
}*/

int check_null_args(char *s, t_list *d, int control)
{
	int i;

	i = -1;
	//s = quit_null_space(s);
	while (s[++i])
	{
		if (s[i] == ' ' && s[i + 1] == 34 && s[i + 2] == 34 && s[i + 3] == ' ')
			control = 1;
		else if (s[i] == ' ' && s[i + 1] == 39 && s[i + 2] == 39 && s[i + 3] == ' ')
			control = 1;
		else if ((s[i] == 34 && s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
			control = 1;
	}
	d->read_line = change_null_args(s, d);
	if (control == 1)
		return (-1);
	return (0);
}

char *ft_split_line(char *s, int i) //funcion para splitear la linea en caso de que haya un pipe
{
	int j;
	char *res;

	j = -1;
	res = malloc(sizeof(char) * i);
	if (!res)
		ft_free();
	while (++j < i)
		res[j] = s[j];
	res[i] = '\0';
	return (res);
}

void ft_define_cmd_line(char *s, t_list *d) //funcion para detectar pipe y si lo hay guardar el comando antes del pipe para ejecutar solo eso
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			while (s[++i] == 34)
				;
		}
		if (s[i] == 39)
		{
			while (s[++i] == 39)
				;
		}
		if (s[i] == '|')
			d->cmd_line = ft_split_line(s, i);
	}
}

char *ft_quit_spaces(char *s) //funcion para quitar los espacios que hay antes del primero comando ya que son innecesarios
{
	int i;
	int j;
	char *res;

	i = -1;
	j = 0;
	while (s[++i] == ' ')
		;
	res = (char *)malloc(sizeof(char) * ft_strlen(s) - i + 1);
	if (!res)
		ft_free();
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	free(s);
	return(res);
}

int parsing(char *s, t_list *d) //funcion parsing para quitar dquote y llamar a mas funciones
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
		d->dolar_question = 1;
		return (0);
	}
	choose_arg(s, d);
	if (s[0] == ' ')
		d->read_line = ft_quit_spaces(s);
	//ft_define_cmd_line(s, d);
	return (0);
}
