#include "../inc/minishell.h"

static int ft_check_wrong_let_export(char c)
{
	if (c == '?' || c == '!' || c == '.'
		|| c == '+' || c == '}' || c == '{' || c == '-' || c == 92
		|| c == '[' || c == ']' || c == '@' || c == '*' || c == '#'
		|| c == '^' || c == '~') //c == '=' ||
	{
		return (1);
	}
	return (0);
}

char *ft_quit_last_char(char *s, int i)
{
	char *res;
	int j;

	j = -1;
	while (s[i])
	{
		if (ft_check_wrong_let_export(s[i]) == 0 && s[i + 1] && s[i + 1] == '+' && s[i + 2] && s[i + 2] == '=')
			break ;
		i++;
	}
	res = malloc(sizeof(char) * ft_strlen(s));
	if (!res)
		exit_error("Error malloc", 22);
	while (++j <= i)
		res[j] = s[j];
	i++;
	while(s[++i])
	{
		res[j] = s[i];
		j++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

/*int ft_check_conditions(char *s, int i)
{

}*/

int parse_equal(char *s, int i) //funcion que controla si hay caracteres o combinaciones de caracteres que provoquen que no se pueda realizar el export
{
	int correct;

	correct = 0;
	while (s[i])
	{
		if (ft_check_wrong_let_export(s[i]) == 0 && s[i + 1] && s[i + 1] == '+' && s[i + 2] && s[i + 2] == '=')
			return (-2);
		else if (s[i] == '!' && s[i + 1] && s[i + 1] != '=')
		{
			printf("bash: %s: event not found\n", s);
			return (-1);
		}
		else if (ft_check_wrong_let_export(s[i]) == 1 || ft_isdigit(s[0]) == 1)
		{
			printf("bash: export: `%s': not a valid identifier\n", s);
			return (-1);
		}
		if (s[i] == '=')
			correct++;
		i++;
	}
	if (correct == 0 || i == 1 || i == correct)
		return (-1);
	return (0);
}

void del_exist_variable(char *full_var, t_cmd *cmd)
{
	int i;
	char *var;
	int len;
	int j;

	i = 0;
	len = 0;
	while (full_var[len] && full_var[len] != '=')
		len++;
	while (i < cmd->env->num_env)
	{
		while (cmd->env->env[i] == NULL && i < cmd->env->num_env)
			i++;
		if (i >= cmd->env->num_env)
			break;
		var = cmd->env->env[i];
		j = -1;
		while (++j != len)
			if (full_var[j] != var[j])
				break ;
		if (j == len)
			cmd->env->env[i] = NULL;
		i++;
	}
}

//⚠️implementar valor variables de otras variables con $ , pero sobretodo el que una nueva variable tenga el valor de 2 o mas variables de entorno⚠️

int export_parse(t_cmd *cmd, char *array, int j, int control)
{
	int i;

	i = 0;
	while (cmd->arg[i])
	{
		del_exist_variable(cmd->arg[i], cmd);
		j = parse_equal(cmd->arg[i], 0);
		if (j == -2)
		{
			cmd->arg[i] = ft_quit_last_char(cmd->arg[i], 0);
			ft_export(&cmd);
			return (-1);
		}
		else if (j == -1)
			array[i] = '0';
		else
		{
			array[i] = '1';
			control++;
		}
		i++;
	}
	array[i] = '\0';
	if (control == 0)
		return(-1);
	return (0);
}

void add_new_vars2(t_cmd *cmd, char *binary_array, int i, char **aux) //segunda parte de funcion que calcula cuantas variables nuevas hay para crear la reserva de memoria debida para luego poder hacer el realloc
{
	int j;

	j = -1;
	while (binary_array[++j])
	{
		if (binary_array[j] == '1')
		{
			aux[i] = cmd->arg[j];
			i++;
		}
	}
	cmd->env->env = (char **)malloc(sizeof(char *) * cmd->env->num_env);
	if (cmd->env->env == NULL)
		exit_error("Error malloc", 23);
	i = -1;
	while (++i < cmd->env->num_env)
		cmd->env->env[i] = aux[i];
}

int add_new_vars1(t_cmd *cmd, char *binary_array) //primera parte de funcion que calcula cuantas variables nuevas hay para crear la reserva de memoria debida para luego poder hacer el realloc
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
	aux = malloc(sizeof(char *) * (cmd->env->num_env + new_envs));
	if (!aux)
		exit_error("Error malloc", 24);
	i = 0;
	while (i < cmd->env->num_env)
	{
		aux[i] = cmd->env->env[i];
		i++;
	}
	free(cmd->env->env);
	printf("A %d\n", cmd->env->num_env);
	cmd->env->num_env = cmd->env->num_env + new_envs;
	printf("D %d\n", cmd->env->num_env);
	add_new_vars2(cmd, binary_array, i, aux);
	return (0);
}

static int var_string_cmp(char *s1, char *s2) //funcion strcmp modificada para variables de entorno
{
	size_t i;

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
		exit_error("Error malloc", 25);
	while(s1[++j])
		result[j - 1] = s1[i + j];
	result[j] = '\0';
	return (result);
}

char *check_same_var(t_cmd *cmd, char *aux) //funcion para checkear si hay una variable de entorno igual que lo que me han mandado por parametro
{
	int i;
	char *result;

	i = -1;
	result = NULL;
	printf("AL PEDO\n");
	while (++i < cmd->env->num_env)
	{
		if (var_string_cmp(aux, cmd->env->env[i]) == 0)
		{
			printf("ENTRO\n");
			result = add_var_value(cmd->env->env[i]);
			return(result);
		}
	}
	return(NULL);
}

char *replace_dolar(t_cmd *cmd, char *var, int i) //funcion para añadir una string que sea lo que va despues del $
{
	char *aux;
	int j;

	j = 0;
	while (var[i] && var[i] != '$')
		i++;
	i++;
	while (var[i + j] && var[i + j] != 34 && var[i + j] != 39)
		j++;
	aux = malloc(sizeof(char) * j + 1);
	if (!aux)
		exit_error("Error malloc", 26);
	j = -1;
	while (var[++j + i] && var[i + j] != 34 && var[i + j] != 39)
		aux[j] = var[i + j];
	aux[j] = '\0';
	aux = check_same_var(cmd, aux);
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
	while (s1[i] && s1[i] != '$')
		i++;
	if (!s1[i + 1])
		return (s1);
	result = malloc(sizeof(char) * i + 1);
	if (!result)
		exit_error("Error malloc", 27);
	i = 0;
	while(s1[i] && s1[i] != '$')
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
	while (s1[i] && s1[i] != '$')
		i++;
	result = malloc(sizeof(char) *  i + ft_strlen(s2) + 1);
	if (!result)
		exit_error("Error malloc", 28);
	while (s1[j] && s1[j] != '$')
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
	while (s1[i] && s1[i] != '=')
		i++;
	result = malloc(sizeof(char) *  i + ft_strlen(s2) + 2);
	if (!result)
		exit_error("Error malloc", 29);
	while (s1[++j] && s1[j] != '=')
		result[j] = s1[j];
	result[j] = s1[j];
	j++;
	while (s2[c])
	{
		result[j + c] = s2[c];
		c++;
	}
	result[j + c] = '\0';
	return (result);
}

char *value_var(t_cmd *cmd, char *var) //funcion main para crear una variable nueva que contenga un $variable. Ej a=abc b=$a  el valor de $b es abc.
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
			printf("AQUI SI QUE SII\n");
			result = replace_dolar(cmd, var, j++);
			break;
		}
	}
	if (result == NULL) 
		return (join_value3(var));
	if (var[j] == '$')
		return (join_value(var, result));
	return (join_value2(var, result));
}

int ft_export(t_cmd **cmd)
{
	int i;
	char *binary_array;

	i = -1;
	if ((*cmd)->num_arg == 0)
	{
		print_export_var((*cmd));
		return (0);
	}
	while ((*cmd)->arg[++i] && i <= (*cmd)->num_arg)
		(*cmd)->arg[i] = str_noquotes((*cmd)->arg[i]);
	binary_array = malloc(sizeof(char) * (*cmd)->num_arg + 1);
	if (!binary_array)
		exit_error("Error malloc", 21);
	if (export_parse((*cmd), binary_array, 0, 0) == -1)
		return (1);
	add_new_vars1((*cmd), binary_array);
	return (0);
}

/*
Cuando me mandan el valor de la var entre "" se lia en la funcion check_dolar_export ya que son argumentos diferentes
*/

/*int ft_export(t_cmd **cmd)
{
	int i;
	int j;
	char *binary_array;

	i = -1;
	j = 0;
	if ((*cmd)->num_arg == 0)
	{
		print_export_var((*cmd));
		return (0);
	}
	while ((*cmd)->arg[++i] && i <= (*cmd)->num_arg)
	{
		(*cmd)->arg[i] = remove_quotes((*cmd)->arg[i], 34);
		(*cmd)->arg[i] = remove_quotes((*cmd)->arg[i], 39);
		if (check_dolar_export((*cmd)->arg[i]) == 1)
		{
			(*cmd)->arg[i] = value_var((*cmd), (*cmd)->arg[i]);
			j++;
		}
		printf("ARG: %s\n", (*cmd)->arg[i]);
	}
	if (j == 0)
		return (0);
	binary_array = malloc(sizeof(char) * (*cmd)->num_arg + 1);
	if (!binary_array)
		exit_error("Error malloc", 21);
	if (export_parse((*cmd), binary_array, 0, 0) == -1)
		return (0);
	add_new_vars1((*cmd), binary_array);
	return (0);
}*/

