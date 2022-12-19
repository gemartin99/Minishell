#include "../inc/minishell.h"

int	ft_count_pipes(char *s) //funcion que retorna la cantidad de pipes que hay en la linea
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (s[++i])
	{
		if (s[i] == '|' && (s[i + 1] == '|' || s[i + 1] == '\0'))
		{
			printf("DOBLE PIPE NO PERMITIDO\n");
			//setear flag sintax error
		}
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

char **fill_memory(char *s, char **res)
{
	int i;
	int start;
	int pos;

	i = -1;
	start = 0;
	pos = 0;
	while (s[++i])
	{
		if ((s[i + 1] == '|' || s[i + 1] == '\0') && s[i] != '|')
		{
			res[pos] = ft_substr(s, start, i - start + 1);
			if (res[pos] == NULL)
				exit_error("Error malloc", 54);
			pos++;
		}
		if (s[i] == '|' && (s[i + 1] != '|' || s[i + 1] != '\0'))
			start = i + 1;
	}
	res[pos] = NULL;
	return (res);
}

int check_pipe_arg(char *s)
{
	int i;
	int res;

	i = -1;
	res = -1;
	while (s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			res = 0;
	}
	return (res);
}

//check pipe y despues null
char **ft_split_pipes(char *s)
{
	char **res;
	int i;

	i = -1;
	res = ft_calloc(sizeof(char *) , (ft_count_pipes(s) + 2));
	if (!res)
		exit_error("Error malloc", 54);
	res = fill_memory(s, res);
	while (res[++i])
	{
		if (check_pipe_arg(res[i]) == -1)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			//setear flag sintax error
		}
	}
	return (res);
}