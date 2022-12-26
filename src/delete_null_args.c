/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_null_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:20:50 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 02:20:53 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

//funcion para quitar argumentos nulos sin espacios antes y despues
static char	*quit_null(char *s, int i)
{
	char	*res;

	s[i] = 27;
	s[i + 1] = 27;
	res = ft_strdup(s);
	free(s);
	return (remove_quotes(res, 27));
}

//funcion para quitar argumentos nulos si 
//hay espacios antes y despues del argumento
static char	*quit_null_space(char *s, int i)
{
	int		j;
	char	*res;

	s[i] = 48;
	s[i + 1] = ';';
	j = -1;
	res = malloc(sizeof(char) * ft_strlen(s));
	if (!res)
		exit_error("Error malloc", 10);
	while (++j < i)
		res[j] = s[j];
	while (s[j + 1])
	{
		res[j] = s[j + 1];
		j++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

//funcion que quita o modifica (para posteriormente quitar) los argumentos nulos
char	*change_null_args(char *s, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == 34 && s[i + 1] && s[i + 1] != 34)
			|| (s[i] == 39 && s[i + 1] && s[i + 1] != 39))
				i = get_next_quote(i + 1, s, s[i]);
		if (s[i] == 32 && (s[i + 1] == 34 || s[i + 1] == 39) && (s[i + 2] == 34
				|| s[i + 2] == 39) && (s[i + 3] == 32 || !s[i + 3]))
		{
			i++;
			s = quit_null_space(s, i);
			s = change_null_args(s, cmd);
		}
		else if ((s[i] == 34 && s[i + 1]
				&& s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
		{
			s = quit_null(s, i);
			cmd->num_arg--;
			return (change_null_args(s, cmd));
		}
	}
	return (s);
}

//funcion que comprueba si hay null args
int	check_null_args(char *s)
{
	int	i;
	int	doubles;
	int	simples;

	doubles = 1;
	simples = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
				doubles *= -1;
		if (s[i] == 39)
			simples *= -1;
		if (s[i] == ' ' && s[i + 1] == 34 && s[i + 2] == 34 && s[i + 3] == ' ')
			return (-1);
		else if (s[i] == ' ' && s[i + 1] == 39
			&& s[i + 2] == 39 && s[i + 3] == ' ')
			return (-1);
		else if ((s[i] == 34 && s[i + 1] == 34 && simples != -1)
			|| (s[i] == 39 && s[i + 1] == 39 && doubles != -1))
			return (-1);
	}
	return (0);
}
