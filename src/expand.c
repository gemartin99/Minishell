#include "../inc/minishell.h"

static int ft_isdigit_special(int i) //funcion que checkea si es un numero o caracter especial
{
	if (i == '*' || i == '@' || i == 92)
		return (1);
	else if (i < 48 || i > 57)
		return (0);
	return (1);
}

int check_dolar(char *line) //funcion para checkear si hay un dolar en la linea que me mandan
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			i++;
		}
		if (line [i] == 34)
		{
			while (line[++i] && line[i] != 34)
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

char *change_dolar_x_var(t_msh cmd, char *s)
{
	if (check_dolar_and_digit(s) == 0)
		s = quit_dollar_and_digit(s);
	if (check_dolar_echo(s) == 0)
		return (s);
	d->control_var_reminder = 0;
	s = ft_change_var(cmd, s);
	if (check_dolar_echo(s) == 1)
		change_dolar_x_var(cmd);
	d->echo_control = 1;
	if (d->control_var_reminder == 1)
	{
		d->read_line = ft_strjoin_special(d->read_line, d->var_reminder, 0, 0);
		d->control_var_reminder = 0;
	}
	parsing(d->read_line, d);
	if (check_dolar_echo(d->read_line) == 1)
		change_dolar_x_var(d);
	return (d->read_line);
}

void expand(t_cmd *cmd)
{
	int i;

	i = -1;
	while(cmd->arg[++i])
	{
		if (check_dolar(cmd->arg[i]) == 1)
			cmd->arg[i] = change_dolar_x_var(cmd, cmd->arg[i]);

	}
}
