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
	//printf("prueba %s\n", s);
	if (s[0] != '-')
	{
		//printf("taamal");
		return (-1);
	}
	while (s[++i])
	{
		//printf("letra: %c", s[i]);
		if (s[i] == 'n')
			;
		else
			return (-1);
	}
	return (0);
}

int check_quotation_mark(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int check_finish_dash_n(char *line, int i, t_list *d)
{
	int num_of_n;
	int j;

	j = 0;
	num_of_n = 0;
	if ((line[i - 1] == 34 || line[i - 1] == 39) && line[i + 2] == ' ')
		write(1, "-n ", 3);
	if (ft_strlen(line) > 7 && (line[i - 1] == 34 || line[i - 1] == 39) && line[i] == '-' 
		&& line[i + 1] == 'n' && (line[i + 2] == 34 || line[i + 2] == 39) && line[i + 3] == ' ')
	{
		while(line[i] != ' ')
			i++;
		while (line[++i])
			write(1, &line[i], 1);
		return (i);
	}
	while (line[++i] == 'n')
		num_of_n++;
	while (line[i] == 34 || line[i] == 39 || (line[i - 1] == 'n' && line[i] == ' ' && line[i + 1] == '-'))
	{
		if (line[i - 1] == 'n' && line[i] == ' ' && line[i + 1] == '-')
		{
			write(1, "-n ", 3);
			if (d->control == 1)
				write(1, " ", 1);
			i++;
			return (i);
		}
		if (line[i + 1] != ' ')
		{
			d->control = 1;
			if (line[i - 1] == 'n')
				write(1, "-", 1);
			while (j < num_of_n)
			{
				write(1, "n", 1);
				j++;
			}
		}
		i++;
	}
	//analizar 
	while (line[i] == ' ')
	{
		if (line[i] != ' ')
			write(1, &line[i + 1], 1);
		i++;
	}
	return (i);
}

void special_echo_n(char *line, t_list *d)
{
	int i;

	i = 0;
	d->control = 0;
	while (line[i] != ' ')
		i++;
	while (line[++i] == 34 || line[i] == 39)
		;
	while (line[i] == '-' && line[i + 1] == 'n')
		i = check_finish_dash_n(line, i, d);
	while (line[i])
	{
		if (line[i] != 34 && line[i] != 39)
			write(1, &line[i], 1);
		i++;
	}
	if (d->control == 1)
		write(1, "\n", 1);
}

void echo_with_quotes(char *line)
{
	int i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while(line[++i])
	{
		if (line[i] != 39 && line[i] != 34)
			write(1, &line[i], 1);
	}
	write (1, "\n", 1);
}

int check_dolar(char *line)
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

/*
char *delete_null_args2(char *line, char *result)
{
	int i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
			i = i + 2;
		if (line[i])
		{
			result[i] = line[i]; 
			i++;
		}
	}
	result[i] = '\0';
	return(result);
}

char *delete_null_args(char *line)
{
	int i;
	int len;
	char *result;

	result = NULL;
	i = 0;
	while (line[i])
		i++;
	len = i;
	i = 0;
	while (line[i])
	{
		if ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
		{
			if (result)
				free(result);
			len = len - 2;
			result = malloc(sizeof(char) * (len + 1));
			if (!result)
				ft_free();
		}
		i++;
	}
	result = delete_null_args2(line, result);
	printf("result: |%s|\n", result);
	return(line);
}
*/

int ft_echo(t_list *d)
{
	int i;

	i = 0;
	//d->read_line = delete_null_args(d->read_line);
	if (check_dolar(d->read_line) == 1)
	{
		printf("hay un dolar en la readline\n");
	}
	if (d->num_args == 1 && check_echo_word(d->argu[0]) == 0)
		return (write(1, "\n", 1) - 1);
	/*if (check_quotation_mark(d->read_line) == 1 && check_dash_n(d->argu[1]) == 0)
	{
		//printf("entro aqui \n");
		special_echo_n(d->read_line, d);
		return (0);
	}
	else if (check_quotation_mark(d->read_line) == 1)
	{
		echo_with_quotes(d->read_line);
		return (0);
	}*/
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