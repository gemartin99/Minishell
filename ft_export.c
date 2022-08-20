#include "minishell.h"

int parse_equal(char *s)
{
	int i;
	int correct;

	i = 0;
	correct = 0;
	printf("aqui0.2.1\n");
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
	printf("aqui0.2.2\n");
	if (correct == 0 || i == 1 || (i == 2 && correct == 2))
	{
		printf("aqui0.2.3\n");
		return (-1);
	}
	printf("aqui0.3\n");
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
	printf("aqui0.1.0\n");
	while (full_var[len] != '=')
		len++;
	printf("aqui0.1.1\n");
	while (i < d->num_env)
	{
		//mirar cuando llega una variable de entorno nula;
		while (d->ent_var[i] == NULL && i < d->num_env)
			i++;
		if (i >= d->num_env)
			break;
		printf("vueltas al bucle %d\nnumero variables %d\n", i, d->num_env);
		printf("hola\n");
		var = d->ent_var[i];
		j = -1;
		printf("hola1\n");
		while (++j != len)
			if (full_var[j] != var[j])
				break ;
		if (j == len)
		{
			printf("entro en el if del while \n");
			d->ent_var[i] = NULL;
		}
		printf("hola2\n");
		i++;
	}
	printf("aqui0.1.3\n");
}

int export_parse(t_list *d, char *array)
{
	int i;
	int j;
	int control;

	i = 1;
	j = 0;
	control = 0;
	//printf("hola-1\n");
	printf("aqui0.1\n");
	while (d->num_args - 1 > i - 1) 
	{
		del_exist_variable(d->argu[i], d);
		printf("argu[i]: |%s|\n", d->argu[i]);
		if (parse_equal(d->argu[i]) == -1)
			array[i - 1] = '0';
		else
		{
			array[i - 1] = '1';
			control++;
		}
		i++;
	}
	printf("aqui0.4\n");
	//printf("%s\n", array);
	//printf("hola0\n");
	array[i - 1] = '\0';
	if (control == 0)
		return(-1);
	printf("aqui0.5\n");
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

int add_new_vars(t_list *d, char *binary_array)
{
	char **aux;
	int i;
	int j;
	int guarrada;

	i = -1;
	guarrada = 0;
	printf("aqui\n");
	while (binary_array[++i])
	{
		if (binary_array[i] == '1')
			guarrada++;
	}
	printf("aqui1\n");
	aux = malloc(sizeof(char *) * (d->num_env + guarrada));
	if (!aux)
		ft_free();
	i = 0;
	while (i < d->num_env)
	{
		aux[i] = d->ent_var[i];
		i++;
	}
	printf("aqui2\n");
	//printf("hola3\n");
	//printf("i: %d\n", i);
	//printf("total: %d\n", d->num_env + guarrada);
	free(d->ent_var);
	d->num_env = d->num_env + guarrada;
	j = -1;
	while (binary_array[++j])
	{
		if (binary_array[j] == '1')
		{
			aux[i] = d->argu[j + 1];
			i++;
		}
	}
	printf("aqui3\n");
	//printf("hola4\n");
	//printf("a %s\n", aux[i - 1]);
	d->ent_var = (char **)malloc(sizeof(char *) * d->num_env);
	if (d->ent_var == NULL)
		ft_free();
	i = -1;
	while (++i < d->num_env)
		d->ent_var[i] = aux[i];
	printf("aqui4\n");
	//printf("l %s\n", d->ent_var[0]);
	//printf("hola5\n");
	return (0);
}

int ft_export(t_list *d)
{
	int i;
	char *binary_array;

	i = 0;

	printf("aqui0\n");
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
	printf("aqui0.6\n");
	add_new_vars(d, binary_array);
	printf("aqui0.7\n");
	return (0);
}