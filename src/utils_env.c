/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:55:09 by smiro             #+#    #+#             */
/*   Updated: 2022/12/12 12:55:13 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

char	*replace_prime(char *s)
{
	char	*res;
	int		i;
	char	*temp;

	i = 0;
	++s;
	temp = ft_strdup(s);
	res = ft_strdup(getenv("HOME"));
	if (!res)
		exit_error("Error malloc", 50);
	return (ft_strjoin(res, temp));
}

int	check_prime(char *s)
{
	int	i;

	i = -1;
	if (s && s[0] == '~' && (!s[1] || s[1] == '/'))
		return (1);
	return (0);
}

int	wrong_exp(char c)
{
	if (c == '?' || c == '!' || c == '.'
		|| c == '+' || c == '}' || c == '{' || c == '-' || c == 92
		|| c == '[' || c == ']' || c == '@' || c == '*' || c == '#'
		|| c == '^' || c == '~')
	{
		return (1);
	}
	return (0);
}

//funcionar que checkea que en la linea que te llega
//haya algun caracter que no sea un espacio
int	check_only_space(char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\v' || s[i] == '\f'
			|| s[i] == '\r' || s[i] == ' ')
			j++;
	}
	if (j == i)
		return (-1);
	return (0);
}

//funcion para contar todas las variables de entorno que no sean nulas.
int	ft_count_env(char **arg, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i + j < len)
	{
		if (arg[i + j])
			i++;
		else
			j++;
	}
	return (i - j);
}
