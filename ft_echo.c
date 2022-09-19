#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	if (write (fd, &c, 1) != 1)
	{
		printf("FALLO MEMORIA\n");
		ft_free();
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

int check_dash_n(char *s)
{
	int i;

	i = 0;
	if (s[0] != '-')
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

static int var_strcmp_echo(char *s1, char *s2) //funcion strcmp modificada para variables de entorno
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

char *ft_name_var(char *line) //funcion que crea una variable con el nombre que tiene el argumento que me manden cn $ para luego comprarlo con las variables de entorno
{
	int j;
	int i;
	char *result;

	i = position_dolar(line);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"')
		j++;
	result = malloc(sizeof(char) * i + j + 1);
	if (!result)
		ft_free();
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"')
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
	result = malloc(sizeof(char) * ft_strlen(s1) - i);
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

char *ft_change_var(t_list *d, char *line)
{
	char *name_var;
	int i;
	char *result;

	name_var = ft_name_var(line);
	if (!name_var)
		return (NULL);
	i = -1;
	while (++i < d->num_env)
	{
		if (var_strcmp_echo(name_var, d->ent_var[i]) == 0)
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

int check_dolar_echo(char *line) //funcion para checkear si hay un dolar en la linea que me mandan
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int calc_dash_n(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ' ')
			break;
	}
	while (s[++i])
	{
		if (s[i] == ' ')
			break;
	}
	return (i);
}

char *change_dolar_x_var(t_list *d)
{
	d->read_line = ft_change_var(d, d->read_line);
	if (d->read_line == NULL)
		d->read_line = "echo";
	if (check_dolar_echo(d->read_line) == 1)
		change_dolar_x_var(d);
	d->echo_control = 1;
	parsing(d->read_line, d);
	return (d->read_line);
}

//cuando me mandan: echo ""algo genera un espacio y no debe hacerlo.
int ft_echo(t_list *d)
{
	int i;
	int condition;

	condition = 1;
	i = 4;
	if (check_dolar_echo(d->read_line) == 1 && d->echo_control == 0)
		d->read_line = change_dolar_x_var(d);
	if (d->num_args == 1 && check_echo_word(d->argu[0]) == 0)
		return (write(1, "\n", 1) - 1);
	else
	{
		if (check_dash_n(d->argu[1]) == 0)
		{
			condition = 0;
			i = calc_dash_n(d->read_line);
		}
		while (d->read_line[++i])
		{
			if (d->read_line[i] == 34)
			{
				while (d->read_line[++i] != 34)
					write(1, &d->read_line[i], 1);
			}
			else
				write(1, &d->read_line[i], 1);
		}
		if (condition == 1)
			ft_putchar_fd('\n', 1);
		d->echo_control = 0;
		return (0);
	}
	d->echo_control = 0;
	return (0);
}
