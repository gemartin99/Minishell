
#include "../inc/minishell.h"

int ft_count_pipes(char *s) //funcion que retorna la cantidad de pipes que hay en la linea
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (s[++i])
	{
		if (s[i] && s[i] == 34)
			while (s[++i] && s[i] != 34)
				;
		if (s[i] && s[i] == 39)
			while (s[++i] && s[i] != 39)
				;
		if (s[i] == '|')
			res++;
	}
	return (res);
}

int	get_next_quote(int i, char *str, char c) //Devuelve la poscision de la siguiente quote
{
	while (str[i] && str[i] != c)
		i++;
	return (i - 1);
}
