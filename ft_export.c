#include "minishell.h"

int parse_equal(char *s)
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
	if (correct == 0 || i == 1 || (i == 2 && correct == 2))
		return (-1);
	return (0);
}

void del_exist_variable(char *full_var, t_list *d)
{
	int i;
	char *var;
	int len;
	int j;

	i = 0;
	len = 0;
	while (full_var[len] != '=')
		len++;
	while (i < d->num_env)
	{
		while (d->ent_var[i] == NULL && i < d->num_env)
			i++;
		if (i >= d->num_env)
			break;
		var = d->ent_var[i];
		j = -1;
		while (++j != len)
			if (full_var[j] != var[j])
				break ;
		if (j == len)
			d->ent_var[i] = NULL;
		i++;
	}
}

//⚠️implementar valor variables de otras variables con $ , pero sobretodo el que una nueva variable tenga el valor de 2 o mas variables de entorno⚠️

int export_parse(t_list *d, char *array)
{
	int i;
	int j;
	int control;

	i = 1;
	j = 0;
	control = 0;
	while (d->num_args - 1 > i - 1) 
	{
		del_exist_variable(d->argu[i], d);
		if (parse_equal(d->argu[i]) == -1)
			array[i - 1] = '0';
		else
		{
			array[i - 1] = '1';
			control++;
		}
		i++;
	}
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
		if (d->ent_var[i] != NULL)
			printf("declare -x %s\n", d->ent_var[i]);
		i++;
	}
}

void add_new_vars2(t_list *d, char *binary_array, int i, char **aux)
{
	int j;

	j = -1;
	while (binary_array[++j])
	{
		if (binary_array[j] == '1')
		{
			aux[i] = d->argu[j + 1];
			i++;
		}
	}
	d->ent_var = (char **)malloc(sizeof(char *) * d->num_env);
	if (d->ent_var == NULL)
		ft_free();
	i = -1;
	while (++i < d->num_env)
		d->ent_var[i] = aux[i];
}

int add_new_vars1(t_list *d, char *binary_array)
{
	char **aux;
	int i;
	int guarrada;

	i = -1;
	guarrada = 0;
	while (binary_array[++i])
	{
		if (binary_array[i] == '1')
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
	free(d->ent_var);
	d->num_env = d->num_env + guarrada;
	add_new_vars2(d, binary_array, i, aux);
	return (0);
}

int ft_export(t_list *d)
{
	int i;
	char *binary_array;

	i = 0;

	//printf("aqui0\n");
	if (d->num_args == 1)
	{
		print_export_var(d);
		return (0);
	}
	binary_array = malloc(sizeof(char) * d->num_args);
	if (!binary_array)
		ft_free();
	if (export_parse(d, binary_array) == -1)
		return (0);
	//printf("aqui0.6\n");
	add_new_vars1(d, binary_array);
	//printf("aqui0.7\n");
	return (0);
}