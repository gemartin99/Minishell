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
	int new_envs;

	i = -1;
	new_envs = 0;
	while (binary_array[++i])
	{
		if (binary_array[i] == '1')
			new_envs++;
	}
	aux = malloc(sizeof(char *) * (d->num_env + new_envs));
	if (!aux)
		ft_free();
	i = 0;
	while (i < d->num_env)
	{
		aux[i] = d->ent_var[i];
		i++;
	}
	free(d->ent_var);
	d->num_env = d->num_env + new_envs;
	add_new_vars2(d, binary_array, i, aux);
	return (0);
}

static int var_strcmp(char *s1, char *s2) //funcion strcmp modificada para variables de entorno
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
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

char *add_var_value(char *s1) //funcion para añadir el valor de la variable de entorno a nuestra variable result
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	while (s1[i] != '=')
		i++;
	result = malloc(sizeof(char) * ft_strlen(s1) - i);
	if (!result)
		ft_free();
	while(s1[++j])
		result[j - 1] = s1[i + j];
	result[j] = '\0';
	return (result);
}

char *check_same_var(t_list *d, char *aux) //funcion para checkear si hay una variable de entorno igual que lo que me han mandado por parametro
{
	int i;
	char *result;

	i = -1;
	result = NULL;
	while (++i < d->num_env)
	{
		if (var_strcmp(aux, d->ent_var[i]) == 0)
		{
			result = add_var_value(d->ent_var[i]);
			return(result);
		}
	}
	return(NULL);
}

char *replace_dolar(t_list *d, char *var, int i) //funcion para añadir una string que sea lo que va despues del $
{
	char *aux;
	int j;

	j = 0;
	while (var[i] != '$')
		i++;
	i++;
	while (var[i + j])
		j++;
	aux = malloc(sizeof(char) * j + 1);
	if (!aux)
		ft_free();
	j = -1;
	while (var[++j + i])
		aux[j] = var[i + j];
	aux[j] = '\0';
	aux = check_same_var(d, aux);
	return(aux);
}

char *join_value3(char *s1) //lo mismo que la 1 y 2 pero esta aplica a $var que no existen
{
	int i;
	char *result;
	int c;
	int j;

	i = 0;
	c = -1;
	j = 0;
	while (s1[i] != '$')
		i++;
	if (!s1[i + 1])
		return (s1);
	result = malloc(sizeof(char) * i + 1);
	if (!result)
		ft_free();
	i = 0;
	while(s1[i] != '$')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}


char *join_value2(char *s1, char *s2) //lo mismo que la 1 pero es para cuando hay caracteres antes de la variable $VAR
{
	int i;
	char *result;
	int c;
	int j;

	i = 0;
	c = -1;
	j = 0;
	while (s1[i] != '$')
		i++;
	result = malloc(sizeof(char) *  i + ft_strlen(s2) + 1);
	if (!result)
		ft_free();
	while (s1[j] != '$')
	{
		result[j] = s1[j];
		j++;
	}
	while (s2[++c])
		result[j + c] = s2[c];
	result[j + c] = '\0';
	return (result);
}

char *join_value(char *s1, char *s2) //funcion para juntar el nombre de la nueva variable con su valor
{
	int i;
	char *result;
	int c;
	int j;

	i = 0;
	c = 0;
	j = -1;
	while (s1[i] != '=')
		i++;
	result = malloc(sizeof(char) *  i + ft_strlen(s2) + 2);
	if (!result)
		ft_free();
	while (s1[j++] != '=')
		result[j] = s1[j];
	result[j] = s1[j];
	while (s2[c])
	{
		result[j + c] = s2[c];
		c++;
	}
	result[j + c] = '\0';
	return (result);
}

char *value_var(t_list *d, char *var) //funcion main para crear una variable nueva que contenga un $variable
{
	char *result;
	int i;
	int j;

	result = NULL;
	j = 0;
	i = 0;
	while (var[j] && var[j] != '=')
		j++;
	while(var[i + j] && var[++i + j])
	{
		if (var[i + j] == '$')
		{
			result = replace_dolar(d, var, j++);
			break;	
		}
	}
	if (result == NULL)
		return (join_value3(var));
	if (var[j] == '$')
		return (join_value(var, result));
	return (join_value2(var, result));
}

int check_dolar_export(char *var) //checkear que haya un dolar en cada variable que me manden
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	while(var[i] && var[++i])
	{
		if (var[i] == '$')
			return (1);
	}
	return (0);
}
//export "hola=a"    -> elimina o nose que hace que cuando haces env no se printan las env's//
int ft_export(t_list *d)
{
	int i;
	char *binary_array;

	i = 0;
	if (d->num_args == 1)
	{
		print_export_var(d);
		return (0);
	}
	while (d->argu[++i] && i < d->num_args)
	{
		if (check_dolar_export(d->argu[i]) == 1)
			d->argu[i] = value_var(d, d->argu[i]);
	}
	binary_array = malloc(sizeof(char) * d->num_args);
	if (!binary_array)
		ft_free();
	if (export_parse(d, binary_array) == -1)
		return (0);
	add_new_vars1(d, binary_array);
	return (0);
}