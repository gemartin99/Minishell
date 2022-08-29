#include "minishell.h"

int check_echo_word(char *s)
{
	if (s[0] != 'E' && s[0] != 'e')
		return (-1);
	if (s[1] != 'C' && s[1] != 'c')
		return (-1);
	if (s[2] != 'H' && s[2] != 'h')
		return (-1);
	if (s[3] != 'O' && s[3] != 'o')
		return (-1);
	if (s[4])
		return (-1);
	return (0);
}

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

int check_dash_n(char *s)
{
	int i;

	i = 0;
	if (s[0] != '-')
		return (-1);
	while (s[++i])
	{
		//printf("char: %c\n", s[i]);
		if (s[i] == 'n')
			;
		else
			return (-1);
	}
	return (0);
}

int check_dolar_echo(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int ft_echo(t_list *d)
{
	int i;

	i = 0;
	//d->read_line = delete_null_args(d->read_line);
	//while (d->argu[++i])
	//	printf("arg %s\n", d->argu[i]);
	//if (check_dash_n(d->argu[1]) == 0)
	//{
	//	printf("hola\n");
	//	exit (0);
	//}
	if (check_dolar_echo(d->read_line) == 1)
	{
		printf("hay un dolar en la readline\n");
	}
	if (d->num_args == 1 && check_echo_word(d->argu[0]) == 0)
		return (write(1, "\n", 1) - 1);
	else
	{
		if (check_dash_n(d->argu[++i]) == 0)
		{
			//printf("entro\n");
			while (i < d->num_args && check_dash_n(d->argu[++i]) == 0)
				;
			i = i - 1;
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
	}
	//printf("llego hasta aqui \n");
	return (0);
}