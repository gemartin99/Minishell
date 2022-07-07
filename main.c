/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:19:02 by gemartin          #+#    #+#             */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free()
{
	printf("FALLA RESERVA MEMORIA\n");
	exit (0);
}

///////////////////////////////////---LIBFT ⬇️---///////////////////////////////////

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		res = malloc(1);
		if (!res)
			return (0);
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	while (start < ft_strlen(s) && i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	c = 0;
	while (s2[c])
	{
		str[i + c] = s2[c];
		c++;
	}
	str[i + c] = '\0';
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (src[c] != '\0')
		c++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (c);
}

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (0);
	ft_strlcpy (res, s1, ft_strlen(s1) + 1);
	return (res);
}

///////////////////////////////////---LIBFT ⬆️---///////////////////////////////////

int print_echo(char *s, t_list *d, int n)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	if (write(1, &s[0], i) != i)
		return (-1);
	if (n != d->num_args -1)
	{
		if (write(1, " ", 1) != 1)
			return (-1);
	}
	//printf("salgo\n");
	return (0);
}

// arreglar cuando mandas esto ';' que haga el comportamiento original
int ft_echo(t_list *d)
{
	int i;

	//while (++i < d->num_args)
	//	printf("arg %d: %s\n", i, d->argu[i]);
	if (d->num_args == 1)
		return (write(1, "\n", 1) - 1);
	else if (ft_strcmp(d->argu[1], "-n") == 0)
	{
		i = 1;
		while (++i < d->num_args)
			if (print_echo(d->argu[i], d, i) != 0)
				return (-1);
	}
	else
	{
		i = 0;
		while (++i < d->num_args)
			if (print_echo(d->argu[i], d, i) != 0)
				return (-1);
			if (write(1, "\n", 1) != 1)
				return (-1);
	}
	//printf("llego hasta aqui \n");
	return (0);
}

int ft_pwd()
{
	char *s;
	char *res;
	int i;

	i = 0;
	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	getcwd(s, MAXPATHLEN);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[i] = '\n';
	if (write(1, &res[0], i + 1) != i + 1)
		return (-1);
	return (0);
}

char *get_path()
{
	char *s;
	char *res;
	int i;

	i = 0;
	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	getcwd(s, MAXPATHLEN);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[++i] = '\0';
	return (res);
}

/*
char *quit_url_extension(char *path, char *res)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	while (path[--i])
	{
		if (path[i] == '/')
		{
			//path[i] = '/';
			path[i] = '\0';
			break ;
		}
	}
	i = 0;
	res = malloc(sizeof(char) * i + 1);
	i = -1;
	while (path[++i])
		res[i] = path[i];
	res[i] = '\0';
	free(path);
	return (res);
}
*/

int ft_cd(t_list *d)
{
	char *path;
	int i;

	path = get_path();
	i = 0;
	if (d->num_args == 1)
		chdir(getenv("HOME"));
	if (d->num_args == 2)
		chdir(d->argu[1]);
	return (0);
}

int ft_env(t_list *d)
{
	int i;

	i = 0;
	//1printf("%d\n", d->num_env);
	while (i < d->num_env)
	{
		printf("%s\n", d->ent_var[i]);
		i++;
	}
	return (0);
}

///////////////////////////////////---EXPORT ⬇️---///////////////////////////////////

int parse_equal(t_list *d, char *s)
{
	int i;
	int correct;

	i = 0;
	correct = 0;
	while (s[i])
	{
		if (s[0] == '=')
		{
			printf("export: `%s': not a valid identifier\n", s);
			return (-1);
		}
		if (s[i] == '=')
			correct++;
		i++;
	}
	if (correct > 2 || correct == 0 || i == 1 || (i == 2 && correct == 2))
	{
		return (-1);
	}
	return (0);
}

int export_parse(t_list *d, char *array)
{
	int i;
	int j;
	int control;

	i = 1;
	j = 0;
	control = 0;
	while (d->argu[i])
	{
		if (parse_equal(d, d->argu[i]) == -1)
			array[i - 1] = '0';
		else
		{
			array[i - 1] = '1';
			control++;
		}
		i++;
	}
	printf("%s\n", array);
	array[i - 1] = '\0';
	if (control == 0)
		return(-1);
	return (0);
}

void	print_export_var(t_list *d)
{
	int i;

	i = 0;
	while (i < d->num_env)
	{
		printf("declare -x %s\n", d->ent_var[i]);
		i++;
	}
}

int add_new_vars(t_list *d, char *array)
{
	char **aux;
	int i;
	int j;
	int guarrada;

	i = -1;
	guarrada = 0;
	while (array[++i])
	{
		if (array[i] == '1')
			guarrada++;
	}
	aux = malloc(sizeof(char *) * (d->num_env + guarrada));
	if (!aux)
		ft_free();
	i = 0;
	while (i < d->num_env)
	{
		aux[i] = d->ent_var[i];
		i++;
	}
	printf("i: %d\n", i);
	printf("total: %d\n", d->num_env + guarrada);
	free(d->ent_var);
	d->num_env = d->num_env + guarrada;
	j = 0;
	while (array[j])
	{
		if (array[j] == '1')
		{
			printf("i: %d\n", i);
			printf("hola1\n");
			printf("argu: %s\n", d->argu[j + 1]);
			printf("hola2\n");
			aux[i] = d->argu[j + 1];
			i++;
			printf("aux[i]: %s\n", aux[i]);
			printf("hola3\n");
		}
		j++;
	}
	printf("a %s\n", aux[i - 1]);
	d->ent_var = (char **)malloc(sizeof(char *) * d->num_env);
	if (d->ent_var == NULL)
		ft_free();
	i = -1;
	while (++i < d->num_env)
		d->ent_var[i] = aux[i];
	printf("l %s\n", d->ent_var[0]);
	return (0);
}

int ft_export(t_list *d)
{
	int i;
	char *array;

	i = 0;

	if (d->num_args == 1)
	{
		print_export_var(d);
		return (0);
	}
	array = malloc(sizeof(char) * d->num_args);
	if (!array)
		ft_free();
	if (export_parse(d, array) == -1)
		return (0);
	add_new_vars(d, array);
	return (0);
}

///////////////////////////////////---EXPORT ⬆️---///////////////////////////////////

int ft_try_to_exec(t_list *d)
{
	if (d->num_args == 1)
	{
		if (execve ("/usr/bin/ls", d->argu, d->ent_var) == -1)
			//printf("%s\n", d->argu[1]);
			perror("execv failed");
	}
	return (0);
}

int check_fst_arg(t_list *d)
{

	if (ft_strcmp(d->argu[0], "echo") == 0)
		return (ft_echo(d));
	else if (ft_strcmp(d->argu[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(d->argu[0], "cd") == 0)
		return (ft_cd(d));
	else if (ft_strcmp(d->argu[0], "env") == 0)
		return (ft_env(d));
	else if (ft_strcmp(d->argu[0], "export") == 0)
		return (ft_export(d));
	//else if (ft_strcmp(d->argu[0], "exit") == 0)
	//	ft_free(d);
	else
	{
		ft_try_to_exec(d);
	}
	return (0);
}

/////////////////////////////////////---Parse ⬇️---/////////////////////////////////////////////////

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
			|| s[i + 1] == 34) || s[i + 1] == 39)
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
	d->argu = malloc(sizeof(char *) * (d->num_args + 1));
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
		if (s[i] == ' ' || s[i] == 34 || s[i] == 39 && s[i + 1] != ' ')
			start = i + 1;
		if ((s[i] != ' ' && s[i] != 34 && s[i] != 39) && (s[i + 1] == ' ' || s[i + 1] == '\0'
			|| s[i + 1] == 34) || s[i + 1] == 39)
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
		printf("Error , deben haber 2 comillas\n");
		return (0);
	}
	if (choose_arg(s, d) == -1)
		return (-1);
	return (0);
}

/////////////////////////////////////---Parse ⬆️---/////////////////////////////////////////////////

void init_prompt(t_list *d)
{
}
//funcion para checkear el numero de tokens que hay

int init_env(t_list *d, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	d->num_env = i;
	d->ent_var = malloc(sizeof(char *) * (d->num_env));
	if (d->ent_var == NULL)
		return (-1);
	i = 0;
	while (i < d->num_env)
	{
		d->ent_var[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		i++;
	}
	//d->ent_var[i] = NULL;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int i;
	t_list d;

	if (argc != 1)
		return (0);
	if (init_env(&d, envp) == -1)
		return (-1); //ft_free()
	while (1)
	{
		d.quotes = 0;
		init_prompt(&d);
		d.read_line = readline("Minishell 🥵🇪🇸 ->");
		if (d.read_line == NULL)
			break ;
		if (parsing(d.read_line, &d) == -1)
			return (printf("ERROR EN EL PARSING\n"));
		add_history(d.read_line);
		if (d.quotes == 0 && check_fst_arg(&d) == -1)
			return (printf("ERROR DE RETORNO \n"));
	}
	return (0);
}
